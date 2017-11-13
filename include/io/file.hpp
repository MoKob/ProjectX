#ifndef PROJECT_X_IO_FILE_HPP_
#define PROJECT_X_IO_FILE_HPP_

#include <boost/filesystem/path.hpp>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>

#include "io/serialisable.hpp"

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

  // sized containers
  template <class container_type>
  void write_pod_container(container_type const &);
  template <class container_type> void read_pod_container(container_type &);
  template <class container_type>
  void write_serialisable_container(container_type const &);
  template <class container_type>
  void read_serialisable_container(container_type &);

  // write different types of containers (POD/Serialisable) and switch between
  // the appropriate types. Mostly provided for convenience, if you don't know
  // for sure what kind of data your container holds
  template <class container_type> void write_container(container_type const &);
  template <class container_type> void read_container(container_type &);

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

template <typename container_type>
void File::write_pod_container(container_type const &container) {
  std::uint64_t size = container.size();
  write_pod(size);
  stream.write(reinterpret_cast<const char *>(container.data()),
               sizeof(typename container_type::value_type) * size);
}

template <typename container_type>
void File::read_pod_container(container_type &container) {
  std::uint_fast64_t size = 0;
  read_pod(size);
  container.resize(size);
  // TODO this should be possible with container.data(), but results in const
  // ptr, which cannot be filled.
  auto ptr = &container[0];
  stream.read(reinterpret_cast<char *>(ptr),
              sizeof(typename container_type::value_type) * size);
}

template <typename container_type>
void File::write_serialisable_container(container_type const &container) {
  std::uint64_t size = container.size();
  write_pod(size);
  for (auto const &entity : container)
    entity.serialise(*this);
}

template <typename container_type>
void File::read_serialisable_container(container_type &container) {
  std::uint_fast64_t size = 0;
  read_pod(size);
  container.resize(size);
  for (auto &entity : container)
    entity.deserialise(*this);
}

namespace detail {
// Dispatch between POD / non POD files statically based on templates
template <typename container_type>
typename std::enable_if<std::is_pod<typename container_type::value_type>::value,
                        void>::type
dispatch_write(File &file, container_type const &container) {
  file.write_pod_container(container);
}

template <typename container_type>
typename std::enable_if<
    !std::is_pod<typename container_type::value_type>::value, void>::type
dispatch_write(File &file, container_type const &container) {
  static_assert(
      std::is_base_of<Serialisable, typename container_type::value_type>::value,
      "Non POD types need to be serialisables to be read/written.");
  file.write_serialisable_container(container);
}

template <typename container_type>
typename std::enable_if<std::is_pod<typename container_type::value_type>::value,
                        void>::type
dispatch_read(File &file, container_type &container) {
  file.read_pod_container(container);
}

template <typename container_type>
typename std::enable_if<
    !std::is_pod<typename container_type::value_type>::value, void>::type
dispatch_read(File &file, container_type &container) {
  static_assert(
      std::is_base_of<Serialisable, typename container_type::value_type>::value,
      "Non POD types need to be serialisables to be read/written.");
  file.read_serialisable_container(container);
}

} // namespace detail

// dispatch between POD / serialisable types
template <typename container_type>
void File::write_container(container_type const &container) {
  detail::dispatch_write(*this, container);
}

template <typename container_type>
void File::read_container(container_type &container) {
  detail::dispatch_read(*this, container);
}
} // namespace io
} // namespace project_x

#endif // PROJECT_X_IO_FILE_HPP_
