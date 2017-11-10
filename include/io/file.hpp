#ifndef PROJECT_X_IO_FILE_HPP_
#define PROJECT_X_IO_FILE_HPP_

#include <boost/filesystem/path.hpp>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>

namespace project_x {
namespace io {
namespace mode {
typedef std::uint32_t Enum;
// fstream mode
static constexpr Enum mREAD = 1 << 0;
static constexpr Enum mWRITE = 1 << 1;
static constexpr Enum mAPPEND = 1 << 2;
static constexpr Enum mBINARY = 1 << 3;
// file mode
// store/check headers
static constexpr Enum mVERSIONED = 1 << 4;
// requires full match, down to patch
static constexpr Enum mVERSIONED_EXACT = 1 << 5;
// requires match down to minor version only
static constexpr Enum mVERSIONED_MINOR = 1 << 6;
// requires match of major version only
static constexpr Enum mVERSIONED_MAJOR = 1 << 7;
// simply warn on mismatch
static constexpr Enum mVERSIONED_WARNING = 1 << 8;
} // mode

// Managing access to a file, including basic checks for versions/checksums and
// so on
class File {
public:
  File(boost::filesystem::path path, mode::Enum mode);

  // POD types can be read/written directly
  template <typename pod_type> void write_pod(pod_type const &);
  template <typename pod_type> void read_pod(pod_type &);
  template <typename pod_type> void write_pod(std::vector<pod_type> const &);
  template <typename pod_type> void read_pod(std::vector<pod_type> &);

  void close();

protected:
  // use data stored in version.h to check validity of file
  void write_version();
  void read_and_check_version(mode::Enum mode);

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

template <typename pod_type>
void File::write_pod(std::vector<pod_type> const &container) {
  static_assert(std::is_pod<pod_type>::value,
                "Supplied type to writePOD is not a POD type");
  stream.write(reinterpret_cast<const char *>(container.data()),
               sizeof(pod_type) * container.size());
}

template <typename pod_type>
void File::read_pod(std::vector<pod_type> &container) {
  static_assert(std::is_pod<pod_type>::value,
                "Supplied type to readPOD is not a POD type");

  if (container.empty())
    throw std::invalid_argument("Read-POD vector is empty. Did you forget to "
                                "resize before calling read_pod(vector)?");

  stream.read(reinterpret_cast<char *>(container.data()),
              sizeof(pod_type) * container.size());
}

} // namespace io
} // namespace project_x

#endif // PROJECT_X_IO_FILE_HPP_
