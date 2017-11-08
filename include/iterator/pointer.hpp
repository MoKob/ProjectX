#ifndef PROJECT_X_ITERATOR_POINTER_HPP_
#define PROJECT_X_ITERATOR_POINTER_HPP_

#include <iostream>
#include <type_traits>

namespace project_x {
namespace iterator {
// iterating over a set of pointers, adding an additional level of dereferincing
// This class provices the means to iterates as pointers in the form of a
// range-based for loop. Given an array a[0,n-1], a range based for loop will
// provide a[0] ... a[n-1]. In some cases, we might require a, a+n-1 instead.
// The Pointer wrapper essentially adds a level of dereferencing to the for
// loop. Instead of for( v : a ) cout << a << endl, we can write
// for(v:PointerRange(a)) cout << *a << endl. While this might not seem
// beneficial at first, this availability of the PTR allows for both access to
// the next element and for the value. So at every for(v: PointerRange(a)), we
// can also access v+1, v-1 and find the ID of the value we are looking at
template <typename wrapped_type> class Pointer {
public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::add_pointer<wrapped_type>::type;
  using pointer = typename std::add_pointer<value_type>::type;
  using reference = typename std::add_lvalue_reference<value_type>::type;

  Pointer(value_type wrapped);
  Pointer(Pointer<wrapped_type> const &other);

  value_type operator*() const;
  Pointer<wrapped_type> &operator++();
  Pointer<wrapped_type> operator++(int);
  Pointer<wrapped_type> &operator=(Pointer<wrapped_type> &&other);
  Pointer<wrapped_type> operator+(std::ptrdiff_t) const;
  Pointer<wrapped_type> &operator+=(std::ptrdiff_t);

  bool operator==(Pointer<wrapped_type> const &other) const;
  bool operator!=(Pointer<wrapped_type> const &other) const;
  bool operator<(Pointer<wrapped_type> const &other) const;
  bool operator<=(Pointer<wrapped_type> const &other) const;
  bool operator>(Pointer<wrapped_type> const &other) const;
  bool operator>=(Pointer<wrapped_type> const &other) const;

  std::ostream &operator<<(std::ostream &os) const;

private:
  value_type wrapped;
};

template <typename wrapped_type>
Pointer<wrapped_type>::Pointer(value_type wrapped) : wrapped(wrapped) {}

template <typename wrapped_type>
Pointer<wrapped_type>::Pointer(Pointer<wrapped_type> const &other)
    : wrapped(other.wrapped) {}

template <typename wrapped_type>
typename Pointer<wrapped_type>::value_type Pointer<wrapped_type>::
operator*() const {
  return wrapped;
}

template <typename wrapped_type>
Pointer<wrapped_type> &Pointer<wrapped_type>::operator++() {
  ++wrapped;
  return *this;
}

template <typename wrapped_type>
Pointer<wrapped_type> Pointer<wrapped_type>::operator++(int) {
  auto copy = *this;
  ++wrapped;
  return copy;
}

template <typename wrapped_type>
Pointer<wrapped_type> Pointer<wrapped_type>::
operator+(std::ptrdiff_t diff) const {
  auto copy = *this;
  return copy += diff;
}

template <typename wrapped_type>
Pointer<wrapped_type> &Pointer<wrapped_type>::operator+=(std::ptrdiff_t diff) {
  wrapped += diff;
  return *this;
}

template <typename wrapped_type>
Pointer<wrapped_type> &Pointer<wrapped_type>::
operator=(Pointer<wrapped_type> &&other) {
  wrapped = other.wrapped;
  return *this;
}

template <typename wrapped_type>
bool Pointer<wrapped_type>::
operator==(Pointer<wrapped_type> const &other) const {
  return wrapped == other.wrapped;
}

template <typename wrapped_type>
bool Pointer<wrapped_type>::
operator!=(Pointer<wrapped_type> const &other) const {
  return wrapped != other.wrapped;
}

template <typename wrapped_type>
bool Pointer<wrapped_type>::
operator<(Pointer<wrapped_type> const &other) const {
  return wrapped < other.wrapped;
}

template <typename wrapped_type>
bool Pointer<wrapped_type>::
operator<=(Pointer<wrapped_type> const &other) const {
  return wrapped <= other.wrapped;
}

template <typename wrapped_type>
bool Pointer<wrapped_type>::
operator>(Pointer<wrapped_type> const &other) const {
  return wrapped > other.wrapped;
}

template <typename wrapped_type>
bool Pointer<wrapped_type>::
operator>=(Pointer<wrapped_type> const &other) const {
  return wrapped >= other.wrapped;
}

template <typename wrapped_type>
std::ostream &Pointer<wrapped_type>::operator<<(std::ostream &os) const {
  os << wrapped;
  return os;
}

} // namespace iterator
} // namespace project_x

#endif // PROJECT_X_ITERATOR_POINTER_HPP_
