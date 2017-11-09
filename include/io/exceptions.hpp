#ifndef PROJECT_X_IO_EXCEPTIONS_HPP_
#define PROJECT_X_IO_EXCEPTIONS_HPP_

#include <stdexcept>

namespace project_x {
namespace io {

// Version-Mismatch indicates that file compatibility is violated
struct VersionMismatch : public std::invalid_argument {
  using std::invalid_argument::invalid_argument;
};

} // namespace io
} // namespace project_x

#endif // PROJECT_X_IO_EXCEPTIONS_HPP_
