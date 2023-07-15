#ifndef VEC_VEC_H
#define VEC_VEC_H
#include "vec-forward.h"
template <typename T, template <typename> class Allocator>
vec<T, Allocator>::~vec() {
  if (arr != nullptr) allocator.deallocate(arr, cap);
}
template <typename T, template <typename> class Allocator>
constexpr void vec<T, Allocator>::push_back(const T& item) {
  if (sz == cap) resize(std::max(2 * cap, static_cast<size_t>(1)));
  arr[sz++] = item;
}
template <typename T, template <typename> class Allocator>
constexpr void vec<T, Allocator>::resize(size_t new_cap) {
  if (new_cap == cap) return;
  if (new_cap < cap) {
    T* copy = allocator.allocate(new_cap);
    std::copy(arr, arr + std::min(sz, new_cap),
              copy);  /// TODO replace copy with swaps
    allocator.deallocate(arr, cap);
    cap = new_cap;
    arr = copy;
    return;
  }
  if (new_cap > cap) {
    T* copy = allocator.allocate(new_cap);
    std::copy(arr, arr + sz, copy);  /// TODO replace
    if (cap > 0) allocator.deallocate(arr, cap);
    cap = new_cap;
    arr = copy;
    return;
  }
}
template <typename T, template <typename> class Allocator>
constexpr void vec<T, Allocator>::pop_back() {
  if (sz == 0) return;
  if (sz > 0) --sz;
  if (4 * sz < cap) resize((cap + 1) / 2);
}
template <typename T, template <typename> class Allocator>
constexpr T& vec<T, Allocator>::operator[](size_t index) {
  return arr[index];
}
template <typename T, template <typename> class Allocator>
constexpr const T& vec<T, Allocator>::operator[](size_t index) const {
  return arr[index];
}
#endif  // VEC_VEC_H
