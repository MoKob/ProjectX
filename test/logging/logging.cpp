#include "log/logger.hpp"

#include <exception>

// make sure we get a new main function here
#define BOOST_TEST_MODULE Logging
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

BOOST_AUTO_TEST_CASE(throw_on_missing_stream) {
  std::ostringstream oss;
  log::Logger log;
  log.set_level(log::Level::CRITICAL);
  BOOST_CHECK_THROW(log.message(log::Level::INFO, "Test"),
                    std::invalid_argument);
  log.set_stream(&oss);
  log.message(log::Level::INFO, "Hello World!");
  BOOST_CHECK_EQUAL(oss.str(), "[INFO] Hello World!\n");

  log.message(log::Level::DEBUG, "This will not be printed.");
  BOOST_CHECK_EQUAL(oss.str(), "[INFO] Hello World!\n");
}
