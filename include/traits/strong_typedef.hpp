#ifndef PROJECT_X_TRAITS_STRONG_TYPEDEF_HPP_
#define PROJECT_X_TRAITS_STRONG_TYPEDEF_HPP_

#include "traits/typemap.hpp"
#include <iostream>

namespace project_x {
namespace traits {
template <typename base_type, typemap type_tag> struct strong_typedef {
  using value_type = base_type;
  value_type value;

  explicit operator value_type &();
  explicit operator value_type() const;

  value_type base() const;

  // comparisons
  bool operator<(strong_typedef<base_type, type_tag> const) const;
  bool operator<=(strong_typedef<base_type, type_tag> const) const;
  bool operator>(strong_typedef<base_type, type_tag> const) const;
  bool operator>=(strong_typedef<base_type, type_tag> const) const;
  bool operator==(strong_typedef<base_type, type_tag> const) const;
  bool operator!=(strong_typedef<base_type, type_tag> const) const;

  // increment/decrement
  strong_typedef<base_type, type_tag> operator++();
  strong_typedef<base_type, type_tag> operator++(int);
  strong_typedef<base_type, type_tag> operator--();
  strong_typedef<base_type, type_tag> operator--(int);

  // longer shifts
  strong_typedef<base_type, type_tag>
  operator+(strong_typedef<base_type, type_tag> const);
  strong_typedef<base_type, type_tag>
  operator+=(strong_typedef<base_type, type_tag> const);
  strong_typedef<base_type, type_tag>
  operator-(strong_typedef<base_type, type_tag> const);
  strong_typedef<base_type, type_tag>
  operator-=(strong_typedef<base_type, type_tag> const);

  // forward outstream
  friend std::ostream &operator<<(std::ostream &os, strong_typedef const type) {
    os << type.value;
    return os;
  }
};

template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag>::operator value_type &() {
  return value;
}
template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag>::operator value_type() const {
  return value;
}
template <typename base_type, typemap type_tag>
base_type strong_typedef<base_type, type_tag>::base() const {
  return value;
}

// comparisons
template <typename base_type, typemap type_tag>
bool strong_typedef<base_type, type_tag>::
operator<(strong_typedef<base_type, type_tag> const rhs) const {
  return value < rhs.value;
}
template <typename base_type, typemap type_tag>
bool strong_typedef<base_type, type_tag>::
operator<=(strong_typedef<base_type, type_tag> const rhs) const {
  return value <= rhs.value;
}
template <typename base_type, typemap type_tag>
bool strong_typedef<base_type, type_tag>::
operator>(strong_typedef<base_type, type_tag> const rhs) const {
  return value > rhs.value;
}
template <typename base_type, typemap type_tag>
bool strong_typedef<base_type, type_tag>::
operator>=(strong_typedef<base_type, type_tag> const rhs) const {
  return value >= rhs.value;
}
template <typename base_type, typemap type_tag>
bool strong_typedef<base_type, type_tag>::
operator==(strong_typedef<base_type, type_tag> const rhs) const {
  return value == rhs.value;
}
template <typename base_type, typemap type_tag>
bool strong_typedef<base_type, type_tag>::
operator!=(strong_typedef<base_type, type_tag> const rhs) const {
  return value != rhs.value;
}

// increment/decrement
template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator++(int) {
  auto const result = *this;
  ++value;
  return result;
}
template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator++() {
  ++value;
  return *this;
}
template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator--(int) {
  auto const result = *this;
  --value;
  return result;
}
template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator--() {
  --value;
  return *this;
}

// longer shifts
template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator+(strong_typedef<base_type, type_tag> const rhs) {
  auto copy = *this;
  copy += rhs;
  return copy;
}

template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator+=(strong_typedef<base_type, type_tag> const rhs) {
  value += rhs.value;
  return *this;
}

template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator-(strong_typedef<base_type, type_tag> const rhs) {
  auto copy = *this;
  copy -= rhs;
  return copy;
}

template <typename base_type, typemap type_tag>
strong_typedef<base_type, type_tag> strong_typedef<base_type, type_tag>::
operator-=(strong_typedef<base_type, type_tag> const rhs) {
  value -= rhs.value;
  return *this;
}

} // namespace traits
} // namespace project_x

#endif // PROJECT_X_TRAITS_STRONG_TYPEDEF_HPP_
