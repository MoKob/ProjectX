#ifndef PROJECT_X_IO_FILE_HPP_
#define PROJECT_X_IO_FILE_HPP_

#include <boost/filesystem/path.hpp>
#include <fstream>
#include <string>
#include <type_traits>

namespace project_x {
namespace io {

// Managing access to a file, including basic checks for versions/checksums and
// so on
class File {
public:
  enum Mode {
    // fstream mode
    mREAD = 1 << 0,
    mWRITE = 1 << 1,
    mAPPEND = 1 << 2,
    mBINARY = 1 << 3,
    // file mode
    mVERSIONED = 1 << 4,        // store/check headers
    mVERSIONED_EXACT = 1 << 5,  // requires full match, down to patch
    mVERSIONED_MINOR = 1 << 6,  // requires match down to minor version only
    mVERSIONED_MAJOR = 1 << 7,  // requires match of major version only
    mVERSIONED_WARNING = 1 << 8 // simply warn on mismatch
  };

  File(boost::filesystem::path path, Mode mode);

  template <typename pod_type> void write_pod(pod_type const &);

  template <typename pod_type> void read_pod(pod_type &);

protected:
  // use data stored in version.h to check validity of file
  void write_version();
  void read_and_check_version(Mode mode);

  boost::filesystem::path path;
  std::fstream stream;
};

template <typename pod_type> void File::write_pod(pod_type const &data) {
  static_assert(std::is_pod<pod_type>::value,
                "Supplied type to writePOD is not a POD type");
  stream.write(reinterpret_cast<const char *>(&data), sizeof(data));
}

template <typename pod_type> void File::read_pod(pod_type &data) {
  static_assert(std::is_pod<pod_type>::value,
                "Supplied type to readPOD is not a POD type");
  stream.read(reinterpret_cast<char *>(&data), sizeof(data));
}

} // namespace io
} // namespace project_x

#endif // PROJECT_X_IO_FILE_HPP_
