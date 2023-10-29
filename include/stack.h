#ifndef VEC_STACK_H
#define VEC_STACK_H
#include "stack-forward.h"


template<typename T, stack_compatible_container<T> Container>
constexpr void stack<T, Container>::swap(stack<T, Container> &other) noexcept{
    c.swap(other.c);
}

template<typename T, stack_compatible_container<T> Container>
template<class... Args>
decltype(auto) stack<T, Container>::emplace(Args &&... args) {
    return c.emplace_back(std::forward<Args>(args)...);
}

template<typename T, stack_compatible_container<T> Container>
constexpr void stack<T, Container>::push(value_type &&value) {
    c.push_back(value);
}

template<typename T, stack_compatible_container<T> Container>
constexpr typename stack<T, Container>::size_type stack<T, Container>::size() const {
    return c.size();
}

template<typename T, stack_compatible_container<T> Container>
constexpr bool stack<T, Container>::empty() const {
    return c.empty();
}

template<typename T, stack_compatible_container<T> Container>
constexpr typename stack<T,Container>::reference stack<T, Container>::top() {
    return c.back();
}

template<typename T, stack_compatible_container<T> Container>
constexpr stack<T, Container>::stack(const Container &con): c(con){

}

template<typename T, stack_compatible_container<T> Container>
constexpr void stack<T, Container>::pop() {
    c.pop_back();
}

#endif //VEC_STACK_H
