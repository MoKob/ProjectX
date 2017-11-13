#include "io/file.hpp"
#include "io/exceptions.hpp"
#include "io/serialisable.hpp"
#include "log/logger.hpp"
#include "version.h"

#include <cstdint>
#include <exception>
#include <fstream>
#include <sstream>
#include <vector>

// make sure we get a new main function here
#define BOOST_TEST_MODULE File
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

struct Edge {
  std::uint64_t source, target;
};

BOOST_AUTO_TEST_CASE(version_mismatch) {
  // manually write a version header to file
  struct VersionHeader {
    std::uint32_t major;
    std::uint32_t minor;
    std::uint32_t patch;
  };

  VersionHeader header = {version_major, version_minor, version_patch};
  std::ofstream ofs("exact.tmp", std::ios::binary);
  ofs.write(reinterpret_cast<const char *>(&header), sizeof(header));
  ofs.close();

  header.patch++;
  ofs.open("patch.tmp", std::ios::binary);
  ofs.write(reinterpret_cast<const char *>(&header), sizeof(header));
  ofs.close();

  header.minor++;
  ofs.open("minor.tmp", std::ios::binary);
  ofs.write(reinterpret_cast<const char *>(&header), sizeof(header));
  ofs.close();

  header.major++;
  ofs.open("major.tmp", std::ios::binary);
  ofs.write(reinterpret_cast<const char *>(&header), sizeof(header));
  ofs.close();

  BOOST_CHECK_NO_THROW(io::File("exact.tmp",
                                io::mode::mREAD | io::mode::mVERSIONED |
                                    io::mode::mVERSIONED_EXACT));

  BOOST_CHECK_THROW(io::File("patch.tmp",
                             io::mode::mREAD | io::mode::mVERSIONED |
                                 io::mode::mVERSIONED_EXACT),
                    io::VersionMismatch);
  BOOST_CHECK_THROW(io::File("minor.tmp",
                             io::mode::mREAD | io::mode::mVERSIONED |
                                 io::mode::mVERSIONED_EXACT),
                    io::VersionMismatch);
  BOOST_CHECK_THROW(io::File("major.tmp",
                             io::mode::mREAD | io::mode::mVERSIONED |
                                 io::mode::mVERSIONED_EXACT),
                    io::VersionMismatch);

  std::ostringstream oss, oss2, oss3;
  log::Logger log;
  log.set_stream(&oss);
  log.set_level(log::Level::WARNING);

  BOOST_CHECK_NO_THROW(io::File("exact.tmp",
                                io::mode::mREAD | io::mode::mVERSIONED |
                                    io::mode::mVERSIONED_EXACT |
                                    io::mode::mVERSIONED_WARNING));
  BOOST_CHECK(oss.str().empty());

  BOOST_CHECK_NO_THROW(io::File("patch.tmp",
                                io::mode::mREAD | io::mode::mVERSIONED |
                                    io::mode::mVERSIONED_EXACT |
                                    io::mode::mVERSIONED_WARNING));
  BOOST_CHECK(oss.str().size() > 0);

  log.set_stream(&oss2);
  BOOST_CHECK_NO_THROW(io::File("minor.tmp",
                                io::mode::mREAD | io::mode::mVERSIONED |
                                    io::mode::mVERSIONED_EXACT |
                                    io::mode::mVERSIONED_WARNING));
  BOOST_CHECK(oss2.str().size() > 0);

  log.set_stream(&oss3);
  BOOST_CHECK_NO_THROW(io::File("major.tmp",
                                io::mode::mREAD | io::mode::mVERSIONED |
                                    io::mode::mVERSIONED_EXACT |
                                    io::mode::mVERSIONED_WARNING));
  BOOST_CHECK(oss3.str().size() > 0);
}

BOOST_AUTO_TEST_CASE(unversioned_vector_reading) {
  // plain data, no versioning happening
  std::vector<int> data = {42, 1, 42, 1, 42};
  {
    io::File file("unversioned.tmp", io::mode::mWRITE | io::mode::mBINARY);
    file.write_container(data);
  }

  // now read the data
  {
    std::vector<int> in_data;
    io::File in_file("unversioned.tmp", io::mode::mREAD | io::mode::mBINARY);
    in_file.read_pod_container(in_data);
    for (std::size_t i = 0; i < data.size(); ++i)
      BOOST_CHECK_EQUAL(data[i], in_data[i]);
  }
}

BOOST_AUTO_TEST_CASE(file_does_not_exist) {
  BOOST_CHECK_THROW(io::File file("nirvana.tmp", io::mode::mREAD),
                    std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(append) {
  for (int i = 0; i < 10; ++i) {
    io::File file("append.tmp", io::mode::mAPPEND | io::mode::mBINARY);
    file.write_pod(i);
  }

  io::File file("append.tmp", io::mode::mREAD | io::mode::mBINARY);
  for (int i = 0; i < 10; ++i) {
    int j = 0;
    file.read_pod(j);
    BOOST_CHECK_EQUAL(i, j);
  }
}

BOOST_AUTO_TEST_CASE(pod_vectors) {
  std::vector<int> data = {1, 2, 3, 4, 5, 6};
  {
    io::File file("pod_dispatched.tmp", io::mode::mWRITE | io::mode::mBINARY);
    file.write_container(data);
  }
  {
    io::File file("pod_dispatched.tmp", io::mode::mREAD | io::mode::mBINARY);
    std::vector<int> comp;
    file.read_container(comp);
    BOOST_CHECK_EQUAL(data.size(), comp.size());
    for (std::size_t i = 0; i < std::min(data.size(), comp.size()); ++i) {
      BOOST_CHECK_EQUAL(data[i], comp[i]);
    }
  }
}

BOOST_AUTO_TEST_CASE(serialisable_vectors) {
  struct Ser : io::Serialisable {
    Ser(int val = 0) : data(val) {}
    int data;
    void serialise(io::File &file) const { file.write_pod(data); }
    void deserialise(io::File &file) { file.read_pod(data); }
  };
  std::vector<Ser> data = {{9}, {2}, {3}, {4}, {5}, {6}, {7}};
  {
    io::File file("ser_dispatched.tmp", io::mode::mWRITE | io::mode::mBINARY);
    file.write_container(data);
  }
  {
    io::File file("ser_dispatched.tmp", io::mode::mREAD | io::mode::mBINARY);
    std::vector<Ser> comp;
    file.read_container(comp);
    BOOST_CHECK_EQUAL(data.size(), comp.size());
    for (std::size_t i = 0; i < std::min(data.size(), comp.size()); ++i) {
      BOOST_CHECK_EQUAL(data[i].data, comp[i].data);
    }
  }
}
