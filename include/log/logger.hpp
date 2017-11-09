#ifndef PROJECT_X_LOG_LOGGER_HPP_
#define PROJECT_X_LOG_LOGGER_HPP_

#include <iostream>
#include <string>

#include "util/singleton.hpp"

namespace project_x {
namespace log {

enum class Level { NONE, DEBUG, ERROR, CRITICAL, WARNING, INFO };

// Logger that provides means to output synchronised messages to a dedicated
// stream
class Logger {
public:
  void set_level(Level level);
  void set_stream(std::ostream *os);

  void message(Level level, std::string message_txt);
};

} // namamespace log
} // namespace project_x

#endif // PROJECT_X_LOG_LOGGER_HPP_
