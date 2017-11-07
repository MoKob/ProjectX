#ifndef PROJECT_X_VERSION_H_IN_
#define PROJECT_X_VERSION_H_IN_

/*
 * File is configured by cmake to reflect versioning, as defined in
CmakeLists.txt
 */

#include <cstdint>

namespace project_x {
const constexpr std::uint32_t version_major = @VERSION_MAJOR @;
const constexpr std::uint32_t version_minor = @VERSION_MAJOR @;
const constexpr std::uint32_t version_path = @VERSION_MAJOR @;
}

#endif /* PROJECT_X_VERSION_H_IN_ */
