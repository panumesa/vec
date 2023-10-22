#ifndef VEC_VEC_H
#define VEC_VEC_H
#include "vec-forward.h"
#include "iterator/iterator.h"
#include "cassert"
template <vector_element T, typename Allocator>
vec<T, Allocator>::~vec() {
  if (arr != nullptr) allocator.deallocate(arr, cap);
  sz = cap = 0;
}
template <vector_element T, typename Allocator>
constexpr void vec<T, Allocator>::push_back(const T& item) {
  emplace_back(item);
}
template <vector_element T, typename Allocator>
constexpr void vec<T, Allocator>::push_back(T&& item) {
  emplace_back(std::move(item));
}
template <vector_element T, typename Allocator>
constexpr void vec<T, Allocator>::resize(size_t new_cap) {
    resize_dealloc(resize_alloc(new_cap), new_cap);
    sz = new_cap;
}
template <vector_element T, typename Allocator>
constexpr T* vec<T, Allocator>::resize_alloc(size_t new_cap){
    if (new_cap == cap) return arr;
    return std::allocator_traits<Allocator>::allocate(allocator, new_cap);
}
template <vector_element T, typename Allocator>
constexpr void vec<T, Allocator>::resize_dealloc(T* new_arr,size_t new_cap){
    if(new_cap == cap) return;
    try {
        for (size_t i = 0; i < std::min(sz,new_cap); ++i) {
            std::allocator_traits<Allocator>::construct(allocator, new_arr + i, std::move_if_noexcept(arr[i]));
        }
    }
    catch(...){
        std::allocator_traits<Allocator>::deallocate(allocator,arr, cap);
        std::allocator_traits<Allocator>::deallocate(allocator, new_arr, new_cap);
        throw std::runtime_error("123");
    }
    if(cap != 0) std::allocator_traits<Allocator>::deallocate(allocator,arr, cap);
    arr = new_arr;
    cap = new_cap;
    sz = std::min(sz, new_cap);

}
template <vector_element T, typename Allocator>
constexpr void vec<T, Allocator>::pop_back() {
  if (sz == 0) return;
  sz--;
  if (4 * sz < cap) shrink((cap + 1) / 2);
}
template <vector_element T, typename Allocator>
constexpr T& vec<T, Allocator>::operator[](size_t index) {
  return arr[index];
}
template <vector_element T, typename Allocator>
constexpr const T& vec<T, Allocator>::operator[](size_t index) const {
  return arr[index];
}
template <vector_element T, typename Allocator>
template <typename... args>
constexpr void vec<T,Allocator>::emplace_back(args&&... pack){
  if (sz == cap) {
     size_t new_cap = std::max(2 * cap, static_cast<size_t>(1));
     T* mem = resize_alloc(new_cap);
     std::allocator_traits<Allocator>::construct(allocator, mem + sz, std::forward<args&&...>(pack)...);
     resize_dealloc(mem,new_cap);
     sz++;
     return;
  }
  std::allocator_traits<Allocator>::construct(allocator, arr + sz++, std::forward<args&&...>(pack)...);
  //std::vector<int> v = {1,2,3,4};
  //v.push_back(v[0]);   {..,..,..,..,..,..,..,..} -> {..,..,..,..,1,..,..,..} -> v=0;
  }
  template <vector_element T, typename Allocator>
  vec<T,Allocator>::vec(const vec<T, Allocator>& copy):
      allocator(std::allocator_traits<Allocator>::select_on_container_copy_construction(copy.allocator)),
      sz(copy.sz), cap(copy.cap){
    std::copy(copy.arr, copy.arr + copy.sz, arr);
}
template <vector_element T, typename Allocator>
constexpr void vec<T,Allocator>::swap(vec<T,Allocator>& second) noexcept{
    if(this == &second) return;
    std::swap(arr,second.arr);
    std::swap(sz,second.sz);
    std::swap(cap,second.cap);
    if constexpr (std::allocator_traits<Allocator>::propagate_on_container_swap::value)
        swap(allocator, second.allocator);
}
template <vector_element T, typename Allocator>
constexpr void vec<T,Allocator>::move_swap(vec<T,Allocator>& second) noexcept{
    if(this == &second) return;
    std::swap(arr,second.arr);
    std::swap(sz,second.sz);
    std::swap(cap,second.cap);
    if constexpr (std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value)
        swap(allocator, second.allocator);
}
template <vector_element T, typename Allocator>
constexpr void vec<T,Allocator>::copy_swap(vec<T,Allocator>& second) noexcept{
    if(this == &second) return;
    std::swap(arr,second.arr);
    std::swap(sz,second.sz);
    std::swap(cap,second.cap);
    if constexpr (std::allocator_traits<Allocator>::propagate_on_container_copy_assignment::value)
        swap(allocator, second.allocator);
}
template <vector_element T, typename Allocator>
vec<T,Allocator>& vec<T,Allocator>::operator=(const vec<T,Allocator>& other){
    if(this == &other) return *this;
    vec<T,Allocator> copy = other;
    copy_swap(copy);
    return *this;
}
template <vector_element T, typename Allocator>
vec<T,Allocator>::vec( vec<T, Allocator>&& copy):
 sz(copy.sz), cap(copy.cap), allocator(std::move(copy.allocator)), arr(copy.arr)
{
    copy.sz = copy.cap = 0;
    copy.arr = nullptr;
}
template <vector_element T, typename Allocator>
vec<T,Allocator>& vec<T,Allocator>::operator=(vec<T,Allocator>&& other){
    if(this == &other) return *this;
    vec<T,Allocator> copy = std::move(other);
    move_swap(copy);
    return *this;
}
template <vector_element T, typename Allocator>
vec<T,Allocator>::vec(std::initializer_list<T> list , Allocator alloc)
: allocator(alloc), sz(0), cap(list.size())
{
    arr = std::allocator_traits<Allocator>::allocate(allocator, cap);
    for (auto&& x : list) {
        std::allocator_traits<Allocator>::construct(allocator, arr + sz++, std::move_if_noexcept(x));
    }
}
template <vector_element T, typename Allocator>
vec<T,Allocator>::vec(size_t size,const T& val, Allocator alloc):sz(size), cap(size),
allocator(alloc), arr(std::allocator_traits<Allocator>::allocate(allocator, size))
{
    for (int i = 0; i < sz; ++i) {
        std::allocator_traits<Allocator>::construct(allocator, arr + i, val);
    }
}
template <vector_element T, typename Allocator>
template <typename InputIterator>
vec<T,Allocator>::vec(InputIterator begin, InputIterator end, Allocator alloc):
sz(std::distance(begin,end)), cap(0), allocator(alloc), arr(std::allocator_traits<Allocator>::allocate(allocator, sz))
{
    for (;begin != end; ++begin) {
        std::allocator_traits<Allocator>::construct(allocator, arr + cap++, *begin);
    }
}
template <vector_element T, typename Allocator>
constexpr size_t vec<T,Allocator>::size() const noexcept{
    return sz;
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::iterator vec<T,Allocator>::begin() noexcept{
    return iterator(arr);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_iterator vec<T,Allocator>::begin() const noexcept{
    return const_iterator(arr);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_iterator vec<T,Allocator>::cbegin() const noexcept{
    return const_iterator(arr);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::reverse_iterator vec<T,Allocator>::rbegin() noexcept{
    return reverse_iterator(arr + sz - 1);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_reverse_iterator vec<T,Allocator>::rbegin() const noexcept{
    return const_reverse_iterator(arr + sz - 1);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_reverse_iterator vec<T,Allocator>::crbegin() const noexcept{
    return const_reverse_iterator(arr + sz - 1);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::iterator vec<T,Allocator>::end() noexcept{
    return iterator(arr + sz);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_iterator vec<T,Allocator>::end() const noexcept{
    return const_iterator(arr + sz);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_iterator vec<T,Allocator>::cend() const noexcept{
    return const_iterator(arr + sz);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::reverse_iterator vec<T,Allocator>::rend() noexcept{
    return reverse_iterator(arr-1);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_reverse_iterator vec<T,Allocator>::rend() const noexcept{
    return const_reverse_iterator(arr-1);
}
template <vector_element T, typename Allocator>
constexpr typename vec<T,Allocator>::const_reverse_iterator vec<T,Allocator>::crend() const noexcept{
    return const_reverse_iterator(arr-1);
}
template <vector_element T, typename Allocator>
constexpr T* vec<T,Allocator>::data() noexcept{
    return arr;
}
template <vector_element T, typename Allocator>
constexpr const T* vec<T,Allocator>::data() const noexcept{
    return arr;
}
template <vector_element T, typename Allocator>
constexpr bool vec<T,Allocator>::empty() const noexcept{
    return sz == 0;
}
template <vector_element T, typename Allocator>
constexpr T& vec<T,Allocator>::front() noexcept{
    return arr[0];
}
template <vector_element T, typename Allocator>
constexpr const T& vec<T,Allocator>::front() const noexcept{
    return arr[0];
}
template <vector_element T, typename Allocator>
constexpr void vec<T,Allocator>::shrink(size_t new_cap){
    assert(sz <= new_cap && new_cap < cap);
    T* newarr = std::allocator_traits<Allocator>::allocate(allocator, new_cap);
    for (int i = 0; i < sz; ++i) {
        try {
            std::allocator_traits<Allocator>::construct(allocator, newarr + i, std::move_if_noexcept(arr[i]));
        }catch(...){
            std::allocator_traits<Allocator>::deallocate(allocator, newarr,new_cap);
            std::allocator_traits<Allocator>::deallocate(allocator,arr,cap);
            sz = cap = 0;
            throw std::runtime_error("ne constructed \n");
        }
    }
    std::allocator_traits<Allocator>::deallocate(allocator,arr,cap);
    arr = newarr;
    cap = new_cap;
}
template<vector_element T, typename Allocator>
template<typename InputIt>
constexpr typename vec<T,Allocator>::iterator vec<T,Allocator>::insert( typename vec<T,Allocator>::iterator pos, InputIt first, InputIt last){
    size_t len_of_gap = std::distance(first, last);
    size_t start = pos - cbegin();
    if(sz + len_of_gap <= cap){
        shift_right_suffix(start, len_of_gap);
        for (int i = start; i < start + len_of_gap ; ++i) {
            std::allocator_traits<Allocator>::construct(allocator,arr + i, *(first++));
        }
    }else{//TODO TRY KECH
        T* newarr = std::allocator_traits<Allocator>::allocate(allocator,sz + len_of_gap);
        for (int i = 0; i < start; ++i) {
            std::allocator_traits<Allocator>::construct(allocator,newarr + i, std::move_if_noexcept(arr[i]));
        }
        for (int i = start; i < start + len_of_gap ; ++i) {
            std::allocator_traits<Allocator>::construct(allocator,newarr + i, *(first++));
        }
        for (int i = start; i < sz  ; ++i) {
            std::allocator_traits<Allocator>::construct(allocator,newarr + i + len_of_gap, std::move_if_noexcept(arr[i]));
        }
        std::allocator_traits<Allocator>::deallocate(allocator,arr,cap);
        arr = newarr;
        cap = sz + len_of_gap;
    }
    sz += len_of_gap;
    return begin() + start + len_of_gap;
}
template<vector_element T, typename Allocator>
constexpr void vec<T,Allocator>::shift_right_suffix(size_t begin, size_t len_of_shift) {
    assert(begin < sz && sz + len_of_shift <= cap);
    for (int i = sz - 1; i >= begin; --i) {
//        arr[i + len_of_shift] = arr[i];
        try{std::allocator_traits<Allocator>::construct(allocator,arr + i + len_of_shift, std::move_if_noexcept(arr[i]));}
        catch(...){
            ~vec<T,Allocator>();
            throw std::runtime_error("shift problem!\n");
        }
    }
}
// std::set<int> s = {2,3,1}; std::vector<int> v(s.begin(), s.end());
#endif  // VEC_VEC_H
