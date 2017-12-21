#ifndef PROJECT_X_CONTAINER_KARY_HEAP_HPP_
#define PROJECT_X_CONTAINER_KARY_HEAP_HPP_

#include "container/heap_element.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <optional>
#include <unordered_map>
#include <vector>

namespace project_x {
namespace container {

// Adaptor for std-set to offer a heap-like interface
template <typename key_type, typename weight_type, int arity = 2>
class KAryHeap {
public:
  KAryHeap();

  using HeapData = HeapElement<key_type, weight_type>;

  // remove the minimum element from the heap
  HeapData pop();
  HeapData peek() const;

  // add a new element to the heap
  void push(key_type key, weight_type weight);

  // check for existing key/value
  bool contains(key_type const key) const;
  std::optional<HeapData> entry(key_type const key) const;

  // update an existing key
  void update(key_type const key, weight_type weight);

  // basic container stuff
  bool empty() const;
  std::size_t size() const;
  void clear();

private:
  const static constexpr std::size_t INVALID_ELEMENT_INDEX = ~0;
  struct HeapEntry {
    weight_type weight;
    std::size_t element_index;
  };

  struct KAryHeapElement {
    HeapData data;
    std::size_t heap_index;
  };

  // swap to elements of the heap
  void swap(std::size_t heap_from, std::size_t heap_to);

  // push an element down the heap
  void sift_down(std::size_t index);
  void sift_up(std::size_t index);

  std::unordered_map<key_type, std::size_t> index;
  std::vector<KAryHeapElement> elements;
  std::vector<HeapEntry> heap;
};

template <typename key_type, typename weight_type, int arity>
KAryHeap<key_type, weight_type, arity>::KAryHeap() {
  clear();
}

template <typename key_type, typename weight_type, int arity>
void KAryHeap<key_type, weight_type, arity>::clear() {
  heap.clear();
  elements.clear();
  index.clear();
}

template <typename key_type, typename weight_type, int arity>
bool KAryHeap<key_type, weight_type, arity>::empty() const {
  return heap.empty();
}

template <typename key_type, typename weight_type, int arity>
std::size_t KAryHeap<key_type, weight_type, arity>::size() const {
  return heap.size();
}

template <typename key_type, typename weight_type, int arity>
void KAryHeap<key_type, weight_type, arity>::swap(std::size_t const heap_from,
                                                  std::size_t const heap_to) {
  std::swap(heap[heap_from], heap[heap_to]);
  elements[heap[heap_from].element_index].heap_index = heap_from;
  elements[heap[heap_to].element_index].heap_index = heap_to;
}

template <typename key_type, typename weight_type, int arity>
HeapElement<key_type, weight_type>
KAryHeap<key_type, weight_type, arity>::peek() const {
  return elements[heap.front().element_index].data;
}

template <typename key_type, typename weight_type, int arity>
HeapElement<key_type, weight_type>
KAryHeap<key_type, weight_type, arity>::pop() {
  auto min = heap.front().element_index;
  swap(0, heap.size() - 1);

  // mark element removed
  elements[heap.back().element_index].heap_index = INVALID_ELEMENT_INDEX;
  heap.pop_back();

  sift_down(0);
  return elements[min].data;
}

template <typename key_type, typename weight_type, int arity>
std::optional<HeapElement<key_type, weight_type>>
KAryHeap<key_type, weight_type, arity>::entry(key_type key) const {
  auto element_index = index.find(key);
  if (element_index != index.end()) {
    return elements[element_index->second].data;
  } else {
    return {};
  }
}

template <typename key_type, typename weight_type, int arity>
void KAryHeap<key_type, weight_type, arity>::push(key_type key,
                                                  weight_type weight) {
  assert(index.find(key) == index.end());
  index[key] = elements.size();
  elements.push_back({{key, weight}, heap.size()});
  heap.push_back({weight, elements.size() - 1});
  sift_up(heap.size() - 1);
}

template <typename key_type, typename weight_type, int arity>
bool KAryHeap<key_type, weight_type, arity>::contains(
    key_type const key) const {
  auto itr = index.find(key);
  return itr != index.end() &&
         elements[itr->second].heap_index != INVALID_ELEMENT_INDEX;
}

template <typename key_type, typename weight_type, int arity>
void KAryHeap<key_type, weight_type, arity>::update(key_type key,
                                                    weight_type weight) {
  assert(index.find(key) != index.end());
  auto element_index = index[key];
  if (elements[element_index].data.weight < weight) {
    elements[element_index].data.weight = weight;
    auto heap_index = elements[element_index].heap_index;
    heap[heap_index].weight = weight;
    sift_down(heap_index);
  } else {
    elements[element_index].data.weight = weight;
    auto heap_index = elements[element_index].heap_index;
    heap[heap_index].weight = weight;
    sift_up(heap_index);
  }
}

template <typename key_type, typename weight_type, int arity>
void KAryHeap<key_type, weight_type, arity>::sift_up(std::size_t index) {
  while (index && heap[index].weight < heap[(index - 1) / arity].weight) {
    auto parent = (index - 1) / arity;
    swap(index, parent);
    index = parent;
  }
}

template <typename key_type, typename weight_type, int arity>
void KAryHeap<key_type, weight_type, arity>::sift_down(std::size_t index) {
  auto base = index * arity + 1;
  auto end = base + arity;
  while (base < heap.size()) {
    auto next = std::min_element(heap.begin() + base,
                                 heap.begin() + std::min(end, heap.size()),
                                 [](auto const &lhs, auto const &rhs) {
                                   return lhs.weight < rhs.weight;
                                 });
    auto next_index = std::distance(heap.begin(), next);

    if (heap[index].weight < heap[next_index].weight)
      return;
    swap(index, next_index);
    index = next_index;
    base = index * arity + 1;
    end = base + arity;
  }
}

} // namespace container
} // namespace project_x

#endif // PROJECT_X_CONTAINER_KARY_HEAP_
