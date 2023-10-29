#ifndef VEC_STACK_FORWARD_H
#define VEC_STACK_FORWARD_H
#include "vec-forward.h"
#include "internal/concepts.h"
template<typename T, stack_compatible_container<T> Container = vec<T>>
class stack{
public:
    using container_type = Container;
    using value_type = Container::value_type;
    using size_type = Container::size_type;
    using reference = Container::reference;
    using const_reference = Container::const_reference;
    explicit constexpr stack(const Container& con = Container());
    [[nodiscard]] constexpr reference top();
    [[nodiscard]] constexpr bool empty() const;
    [[nodiscard]] constexpr size_type size() const;
    constexpr void push(value_type&& value);
    template< class... Args >
    decltype(auto) emplace( Args&&... args );
    constexpr void pop();
    constexpr void swap(stack<T,Container>& other) noexcept;
    constexpr ~stack() = default;
protected:
    Container c;
};


#endif //VEC_STACK_FORWARD_H
