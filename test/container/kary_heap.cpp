#include "container/kary_heap.hpp"

// make sure we get a new main function here
#define BOOST_TEST_MODULE Container
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(binary_heap_operations) {
  // construct a heap
  container::KAryHeap<int, int, 2> heap;
  BOOST_CHECK(heap.empty());
  BOOST_CHECK(heap.size() == 0);

  heap.push(0, 0);
  BOOST_CHECK_EQUAL(heap.size(), 1);
  BOOST_CHECK(heap.contains(0));

  heap.push(1, 1);
  BOOST_CHECK_EQUAL(heap.peek().key, 0);

  heap.update(0, 2);
  BOOST_CHECK_EQUAL(heap.peek().key, 1);
  heap.update(0, 0);
  BOOST_CHECK_EQUAL(heap.peek().key, 0);

  auto entry = heap.pop();
  BOOST_CHECK_EQUAL(entry.key, 0);
  BOOST_CHECK_EQUAL(entry.weight, 0);

  BOOST_CHECK_EQUAL(heap.entry(0)->key, 0);
  BOOST_CHECK_EQUAL(heap.entry(0)->weight, 0);

  BOOST_CHECK(!heap.entry(2));
  BOOST_CHECK(!heap.contains(0));

  heap.clear();
  BOOST_CHECK(heap.empty());
  BOOST_CHECK_EQUAL(heap.size(), 0);

  BOOST_CHECK(!heap.contains(1));
  heap.push(0, 0);
  heap.push(1, 1);
  heap.push(2, 2);
  heap.push(3, 3);
  heap.push(4, 4);
  heap.push(5, 5);
  heap.update(0, 6);
  heap.pop();
  heap.pop();
  heap.pop();
  heap.pop();
  heap.pop();
  BOOST_CHECK_EQUAL(heap.peek().key, 0);
}
