#ifndef VEC_CONCEPTS_H
#define VEC_CONCEPTS_H

#include <concepts>

template<class T>
concept CopyAssignable = std::is_copy_assignable_v<T>;
template<class T>
concept CopyConstructible = std::is_copy_constructible_v<T>;
template<class T>
concept vector_element = CopyAssignable<T> && CopyConstructible<T>;

template<typename Container, typename T>
concept stack_compatible_container = requires(T value, Container c){
    c.pop_back();
    c.push_back(value);
    { c.back() }-> std::same_as<T &>;
};

#endif //VEC_CONCEPTS_H
