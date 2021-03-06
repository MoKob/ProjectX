#ifndef PROJECT_X_IO_SERIALISABLE_HPP_
#define PROJECT_X_IO_SERIALISABLE_HPP_

namespace project_x {
namespace io {

class File;

// Interface for all serialisable objects
class Serialisable {
  virtual void serialise(File &file) const = 0;
  virtual void deserialise(File &file) = 0;
};
} // namespace io
} // namespace project_x

#endif // PROJECT_X_IO_SERIALISABLE_HPP_
