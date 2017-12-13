#include "builder/conversion.hpp"
#include "graph/routing.hpp"

#include <cstdint>
#include <string>
#include <tuple>

// make sure we get a new main function here
#define BOOST_TEST_MODULE Builder
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

// select all three elements
BOOST_AUTO_TEST_CASE(three_data_elements) {
  struct Edge {
    std::tuple<std::uint32_t, std::uint32_t, std::uint32_t> data;
  };

  Edge edge{{1, 2, 3}};

  auto wtd =
      builder::decoration::convert<Edge, graph::WeightTimeDistance>(edge);
  BOOST_CHECK_EQUAL(wtd.weight, 1);
  BOOST_CHECK_EQUAL(wtd.time, 2);
  BOOST_CHECK_EQUAL(wtd.distance, 3);
}

BOOST_AUTO_TEST_CASE(three_data_elements_with_additional_payload) {
  struct Edge {
    std::tuple<std::uint32_t, std::uint32_t, std::uint32_t, std::string> data;
  };

  Edge edge{{1, 2, 3, "Hello, I am a payload"}};

  auto wtd =
      builder::decoration::convert<Edge, graph::WeightTimeDistance>(edge);
  BOOST_CHECK_EQUAL(wtd.weight, 1);
  BOOST_CHECK_EQUAL(wtd.time, 2);
  BOOST_CHECK_EQUAL(wtd.distance, 3);
}
