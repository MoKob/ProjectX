#include "algorithm/union_find.hpp"

// make sure we get a new main function here
#define BOOST_TEST_MODULE UnionFind
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(uf_algo) {
  algorithm::UnionFind uf(10);
  BOOST_CHECK_EQUAL(uf.find(0), 0);
  BOOST_CHECK_EQUAL(uf.find(1), 1);
  BOOST_CHECK_EQUAL(uf.find(2), 2);
  BOOST_CHECK_EQUAL(uf.find(3), 3);
  BOOST_CHECK_EQUAL(uf.find(4), 4);
  BOOST_CHECK_EQUAL(uf.find(5), 5);
  BOOST_CHECK_EQUAL(uf.find(6), 6);
  BOOST_CHECK_EQUAL(uf.find(7), 7);
  BOOST_CHECK_EQUAL(uf.find(8), 8);
  BOOST_CHECK_EQUAL(uf.find(9), 9);

  uf.unite(0, 1);
  uf.unite(0, 2);

  BOOST_CHECK_EQUAL(uf.find(1), uf.find(2));

  uf.unite(4, 4);
  BOOST_CHECK(uf.find(4) != uf.find(0));
  uf.unite(uf.find(0), uf.find(5));
  BOOST_CHECK(uf.find(4) != uf.find(5));
  BOOST_CHECK_EQUAL(uf.find(0), uf.find(5));
  uf.unite(uf.find(6), uf.find(0));
  BOOST_CHECK_EQUAL(uf.find(6), uf.find(5));
}
