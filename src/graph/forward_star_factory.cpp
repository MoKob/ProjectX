#include "graph/forward_star_factory.hpp"
#include "io/file.hpp"

namespace project_x {
namespace graph {
ForwardStar
ForwardStarFactory::produce_from_file(boost::filesystem::path const &path) {
  ForwardStar graph;
  io::mode::Enum mode = io::mode::mREAD | io::mode::mBINARY |
                        io::mode::mVERSIONED | io::mode::mVERSIONED_EXACT |
                        io::mode::mVERSIONED_WARNING;
  io::File file(path, mode);
  graph.deserialise(file);
  return graph;
}
} // namespace graph
} // namespace project_x
