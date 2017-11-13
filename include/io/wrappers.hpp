#ifndef PROJECT_X_IO_WRAPPERS_HPP_
#define PROJECT_X_IO_WRAPPERS_HPP_

#include "io/file.hpp"
#include "io/serialisable.hpp"

namespace project_x {
namespace io {

template <typename base_type>
struct SerialisableContainer : public io::Serialisable {
  SerialisableContainer() : wrapped_object(){};
  SerialisableContainer(base_type wrapped_object_)
      : wrapped_object(wrapped_object_){};

  void serialise(File &) const;
  void deserialise(File &);

  base_type &operator*();
  base_type const &operator*() const;

  base_type wrapped_object;
};

template <typename base_type>
void SerialisableContainer<base_type>::serialise(File &file) const {
  file.write_container(wrapped_object);
}

template <typename base_type>
void SerialisableContainer<base_type>::deserialise(File &file) {
  file.read_container(wrapped_object);
}

template <typename base_type>
base_type &SerialisableContainer<base_type>::operator*() {
  return wrapped_object;
}

template <typename base_type>
base_type const &SerialisableContainer<base_type>::operator*() const {
  return wrapped_object;
}

} // namespace io
} // namespace project_x

#endif // PROJECT_X_IO_WRAPPERS_HPP_
