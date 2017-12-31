#include "traits/strong_typedef.hpp"
#include "traits/typemap.hpp"

#include <sstream>

// make sure we get a new main function here
#define BOOST_TEST_MODULE Traits
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

BOOST_AUTO_TEST_CASE(id_type) {
  using TestID = traits::strong_typedef<int, traits::typemap::tagNodeID>;

  auto id = TestID{1};
  auto id_2 = TestID{2};
  BOOST_CHECK(id != id_2);
  BOOST_CHECK(id < id_2);
  BOOST_CHECK(id <= id_2);
  BOOST_CHECK(id_2 > id);
  BOOST_CHECK(id_2 >= id);

  auto id_2_2 = id;
  ++id_2_2;
  auto id_1_2 = id++;
  id--;

  BOOST_CHECK_EQUAL(id_2, id_2_2);
  BOOST_CHECK_EQUAL(id, id_1_2);

  auto id_1_3 = id_2_2;
  --id_1_3;
  BOOST_CHECK_EQUAL(id, id_1_3);

  BOOST_CHECK_EQUAL(id_2, id + id);
  BOOST_CHECK_EQUAL(id_2 - id, id);

  auto id_2_4 = id_2;
  id_2_4 -= id;
  BOOST_CHECK_EQUAL(id_2_4, id);
  id_2_4 += id;
  BOOST_CHECK_EQUAL(id_2_4, id_2);

  auto base = static_cast<int>(id);
  BOOST_CHECK_EQUAL(base, id.base());

  auto &base_ref = static_cast<int &>(id);
  ++base_ref;
  BOOST_CHECK_EQUAL(id, id_2);
  --id;

  std::ostringstream oss;
  oss << id;

  BOOST_CHECK_EQUAL(oss.str(), "1");
}
