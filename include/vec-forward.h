#ifndef VEC_VEC_FORWARD_H
#define VEC_VEC_FORWARD_H
#include "internal/define.h"
#include "iterator/iterator-forward.h"
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
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = _forward_iterator<value_type>;
    using const_iterator = _forward_iterator<const value_type>;
    using reverse_iterator = _reverse_iterator<value_type>;
    using const_reverse_iterator = _reverse_iterator<const value_type>;
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
  [[nodiscard]] constexpr iterator begin() noexcept;
  [[nodiscard]] constexpr const_iterator begin() const noexcept;
  [[nodiscard]] constexpr const_iterator cbegin() const noexcept;
  [[nodiscard]] constexpr reverse_iterator rbegin() noexcept;
  [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept;
  [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept;
  [[nodiscard]] constexpr iterator end() noexcept;
  [[nodiscard]] constexpr const_iterator end() const noexcept;
  [[nodiscard]] constexpr const_iterator cend() const noexcept;
  [[nodiscard]] constexpr reverse_iterator rend() noexcept;
  [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept;
  [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept;
  [[nodiscard]] constexpr T* data() noexcept;
  [[nodiscard]] constexpr const T* data() const noexcept;
  [[nodiscard]] constexpr bool empty() const noexcept;
  [[nodiscard]] constexpr T& front() noexcept;
  [[nodiscard]] constexpr const T& front() const noexcept;

 private:
  size_t sz = 0;
  size_t cap = 0;
  T* arr = nullptr;
  NO_UNIQUE_ADDRESS Allocator allocator;
  constexpr void move_swap(vec<T,Allocator>& other) noexcept;
  constexpr void copy_swap(vec<T,Allocator>& other) noexcept;
  constexpr T* resize_alloc(size_t new_cap);
  constexpr void resize_dealloc(T* new_arr, size_t new_cap);
};
#endif  // VEC_VEC_FORWARD_H
