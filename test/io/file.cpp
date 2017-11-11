#include "io/file.hpp"
#include "io/exceptions.hpp"
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
    file.write_pod(data);
  }

  // no read the data
  {
    std::ifstream ifs("unversioned.tmp");
    std::vector<int> tmp;
    tmp.resize(data.size());
    ifs.read(reinterpret_cast<char *>(tmp.data()), sizeof(int) * tmp.size());
    for (std::size_t i = 0; i < data.size(); ++i)
      BOOST_CHECK_EQUAL(data[i], tmp[i]);
    ifs.close();

    std::vector<int> in_data;
    io::File in_file("unversioned.tmp", io::mode::mREAD | io::mode::mBINARY);
    BOOST_CHECK_THROW(in_file.read_pod(in_data), std::invalid_argument);
    in_data.resize(data.size());
    in_file.read_pod(in_data);
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
