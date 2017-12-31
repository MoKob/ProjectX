#ifndef PROJECT_X_TRAITS_TYPEMAP_HPP_
#define PROJECT_X_TRAITS_TYPEMAP_HPP_

namespace project_x {
namespace traits {

// a list of tags for each strong typedef
enum class typemap {
  // geometric types
  tagLongitude,
  tagLatitude,
  // ID types
  tagNodeID,
  tagEdgeID
};

} // namespace traits
} // namespace project_x

#endif // PROJECT_X_TRAITS_TYPEMAP_HPP_
