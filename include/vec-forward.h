#ifndef VEC_VEC_FORWARD_H
#define VEC_VEC_FORWARD_H
#include <memory>

 template<class T>
 concept CopyAssignable = std::is_copy_assignable_v<T>;
 template<class T>
 concept CopyConstructible = std::is_copy_constructible_v<T>;
 template<class T>
 concept vector_element = CopyAssignable<T> && CopyConstructible<T>;
 template <vector_element T, typename Allocator = std::allocator<T>>
class vec {
 public:
  vec() = default;
  vec(const vec<T, Allocator>& copy);
  vec(vec<T, Allocator>&& copy);
  vec(std::initializer_list<T> list , Allocator alloc = Allocator());
  vec(size_t size, const T& val = T(), Allocator alloc = Allocator());
  template <typename InputIterator>
  vec(InputIterator begin, InputIterator end, Allocator alloc = Allocator());
  ~vec();
  vec<T,Allocator>& operator=(const vec<T,Allocator>& copy);
  vec<T,Allocator>& operator=(vec<T,Allocator>&& copy);
  constexpr void swap(vec<T,Allocator>& second) noexcept;
  constexpr void push_back(const T& item);
  constexpr void pop_back();
  constexpr void resize(size_t new_cap);
  [[nodiscard]] constexpr T& operator[](size_t index);
  [[nodiscard]] constexpr const T& operator[](size_t index) const;
  template <typename... args>
  constexpr void emplace_back(args&&... pack);
  constexpr void push_back(T&& item);
  constexpr size_t size() const noexcept;
 private:
  size_t sz = 0;
  size_t cap = 0;
  T* arr = nullptr;
  Allocator allocator;
  constexpr void move_swap(vec<T,Allocator>& other) noexcept;
  constexpr void copy_swap(vec<T,Allocator>& other) noexcept;
  constexpr T* resize_alloc(size_t new_cap);
  constexpr void resize_dealloc(T* new_arr, size_t new_cap);
};
#endif  // VEC_VEC_FORWARD_H
