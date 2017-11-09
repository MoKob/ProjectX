#ifndef PROJECT_X_UTIL_SINGLETON_HPP_
#define PROJECT_X_UTIL_SINGLETON_HPP_

#include <memory>
#include <type_traits>

namespace project_x {
namespace util {

// providing singleton functionality for default-constructable objects
template <typename class_type> class Singleton {
public:
  static class_type &instance();

  // no copy / assignment
  Singleton(const Singleton<class_type> &) = delete;
  Singleton &operator=(const Singleton<class_type> &) = delete;

private:
  static std::unique_ptr<class_type> class_instance;
};

// location for static variable
template <typename class_type>
std::unique_ptr<class_type> Singleton<class_type>::class_instance;

template <typename class_type> class_type &Singleton<class_type>::instance() {
  static_assert(std::is_default_constructible<class_type>::value,
                "Singleton only supports default-constructible types.");
  if (class_instance == nullptr)
    class_instance = std::make_unique<class_type>();
  return *class_instance.get();
}

} // namespace util
} // namespace project_x

#endif // PROJECT_X_UTIL_SINGLETON_HPP_
