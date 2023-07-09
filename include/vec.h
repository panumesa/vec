#ifndef VEC_VEC_H
#define VEC_VEC_H
#include <memory>
//template<class T>
//concept CopyAssignable = std::is_copy_assignable_v<T>;
//template<class T>
//concept CopyConstructible = std::is_copy_constructible_v<T>;
//template<class T>
//concept vector_element = CopyAssignable<T> && CopyConstructible<T>;
template <typename T, template<typename> class Allocator = std::allocator>
//requires vector_element<T>
class vec{
public:
    vec() = default;
    ~vec();
    constexpr void push_back(const T& item);
    constexpr void pop_back();
    constexpr void resize(size_t new_cap);
    [[nodiscard]] constexpr T& operator[](size_t index);
    [[nodiscard]] constexpr const T& operator[](size_t index) const;
private:
    size_t sz = 0;
    size_t cap = 0;
    T* arr = nullptr;
    Allocator<T> allocator;
};
#endif //VEC_VEC_H
