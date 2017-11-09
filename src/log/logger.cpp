#include "log/logger.hpp"
#include "util/singleton.hpp"

#include <mutex>
#include <stdexcept>

namespace project_x {
namespace log {

namespace {
const constexpr char *log_level_names[] = {"NONE",     "DEBUG",   "ERROR",
                                           "CRITICAL", "WARNING", "INFO"};

// The logger allows synchronised output to a stream. Requires set_stream to be
// called before messaging anything
class LoggerBase {
public:
  LoggerBase();

  // to use logging, we need to initialise it prior to messaging
  void set_level(Level level);
  void set_stream(std::ostream *os);

  void message(Level level, std::string message_txt);

private:
  std::mutex lock;
  Level level;
  std::ostream *os;
};

} // namespace

LoggerBase::LoggerBase() : level(Level::NONE), os(nullptr) {}

void LoggerBase::set_stream(std::ostream *os_) { os = os_; }
void LoggerBase::set_level(Level const level_) { level = level_; }

void LoggerBase::message(Level const log_level, std::string message) {
  // only log appropriate levels
  if (log_level < level)
    return;

  if (os) {
    std::lock_guard<std::mutex> guard(lock);
    (*os) << "["
          << log_level_names[static_cast<std::underlying_type<Level>::type>(
                 log_level)]
          << "] " << message << "\n";
  } else {
    throw std::invalid_argument("Logging without propper initialisation. "
                                "Please ensure to set an output stream.");
  }
}

void Logger::set_stream(std::ostream *os) {
  auto &logger = util::Singleton<LoggerBase>::instance();
  logger.set_stream(os);
}

void Logger::set_level(Level const level_) {
  auto &logger = util::Singleton<LoggerBase>::instance();
  logger.set_level(level_);
}

void Logger::message(Level const log_level, std::string message) {
// check if we can disable the logging completely to not have any performance
// impact
#ifndef PROJECT_X_DISABLE_LOGGING
  auto &logger = util::Singleton<LoggerBase>::instance();
  logger.message(log_level, message);
#endif
}

} // namespace log
} // namespace project_x
