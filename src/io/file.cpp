#include "io/file.hpp"
#include "io/exceptions.hpp"
#include "version.h"

#include <cstdint>
#include <ios>

namespace project_x {
namespace io {

namespace detail {
struct HeaderVersion {
  std::uint32_t major;
  std::uint32_t minor;
  std::uint32_t patch;
};

// Check if a flag is set in the provided mode
bool is_set(File::Mode mode, File::Mode flag) { return (mode & flag) == flag; }
bool any_of(File::Mode mode, std::uint32_t flags) {
  return (mode & flags) != 0;
}

} // namespace detail

File::File(boost::filesystem::path path_, Mode mode) : path(path_) {
  std::ios_base::openmode file_mode;
  if (detail::is_set(mode, Mode::mREAD)) {
    file_mode |= std::ios::in;
  }

  if (detail::is_set(mode, Mode::mAPPEND)) {
    file_mode |= std::ios_base::app;
  } else if (detail::is_set(mode, Mode::mWRITE)) {
    file_mode |= std::ios_base::out;
  }

  if (detail::is_set(mode, Mode::mBINARY)) {
    file_mode |= std::ios::binary;
  }

  stream.open(path.string(), file_mode);

  if ((detail::is_set(mode, Mode::mWRITE) ||
       detail::is_set(mode, Mode::mAPPEND)) &&
      detail::is_set(mode, mVERSIONED))
    write_version();

  if (detail::is_set(mode, Mode::mREAD) && detail::is_set(mode, mVERSIONED))
    read_and_check_version(mode);
}

void File::write_version() {
  detail::HeaderVersion version = {version_major, version_minor, version_patch};
  write_pod(version);
}

void File::read_and_check_version(File::Mode mode) {
  detail::HeaderVersion version;
  read_pod(version);

  auto const log_or_throw = [mode](std::string message) {
    if (detail::is_set(mode, Mode::mVERSIONED_WARNING)) {
      // log::Message::raise(log::Level::WARNING, std::move(message));
    } else {
      throw VersionMismatch(std::move(message));
    }
  };

  bool requires_major =
      detail::any_of(mode, Mode::mVERSIONED_EXACT | Mode::mVERSIONED_MAJOR);
  if (requires_major && version_major != version.major) {
    std::string message = "Major version mismatch. Got " +
                          std::to_string(version.major) + " but expected " +
                          std::to_string(version_major);
    log_or_throw(std::move(message));
  }

  if (version_minor != version.minor) {
    std::string message = "Minor version mismatch. Got " +
                          std::to_string(version.minor) + " but expected " +
                          std::to_string(version_minor);
    log_or_throw(std::move(message));
  }

  if (version_patch != version.patch) {
    std::string message = "Patch version mismatch. Got " +
                          std::to_string(version.patch) + " but expected " +
                          std::to_string(version_patch);
    log_or_throw(std::move(message));
  }
}

} // namespace io
} // namespace project_x
