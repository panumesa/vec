#ifndef VEC_ITERATOR_H
#define VEC_ITERATOR_H

#include "iterator-forward.h"

template<typename T>
struct std::iterator_traits<_forward_iterator<T>> {
    using difference_type = typename _forward_iterator<T>::difference_type;
    using value_type = typename _forward_iterator<T>::value_type;
    using pointer = typename _forward_iterator<T>::pointer;
    using reference = typename _forward_iterator<T>::reference;
    using iterator_category = typename _forward_iterator<T>::category;
};
template<typename T>
struct std::iterator_traits<_reverse_iterator<T>> {
    using difference_type = typename _reverse_iterator<T>::difference_type;
    using value_type = typename _reverse_iterator<T>::value_type;
    using pointer = typename _reverse_iterator<T>::pointer;
    using reference = typename _reverse_iterator<T>::reference;
    using iterator_category = typename _reverse_iterator<T>::category;
};

template<typename vector_element, typename vector_iterator_implementation>
constexpr std::strong_ordering base_vector_iterator<vector_element, vector_iterator_implementation>::operator<=>(
        const vector_iterator_implementation &other) const noexcept {
    return impl()->Difference(other) <=> 0;
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr bool base_vector_iterator<vector_element, vector_iterator_implementation>::operator==(
        const vector_iterator_implementation &other) const noexcept {
    return pt == other.pt;
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr bool base_vector_iterator<vector_element, vector_iterator_implementation>::operator!=(
        const vector_iterator_implementation &other) const noexcept {
    return pt != other.pt;
}

template<typename vector_element, typename vector_iterator_implementation>
inline constexpr const vector_iterator_implementation *
base_vector_iterator<vector_element, vector_iterator_implementation>::impl() const noexcept {
    return static_cast<const vector_iterator_implementation *>(this);
}

template<typename vector_element, typename vector_iterator_implementation>
inline constexpr vector_iterator_implementation *
base_vector_iterator<vector_element, vector_iterator_implementation>::impl() noexcept {
    return static_cast<vector_iterator_implementation *>(this);
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr
base_vector_iterator<vector_element, vector_iterator_implementation>::base_vector_iterator(vector_element *pt) noexcept
        :pt(pt) {}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_element &base_vector_iterator<vector_element, vector_iterator_implementation>::operator*() noexcept {
    return *pt;
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation &
base_vector_iterator<vector_element, vector_iterator_implementation>::operator++() noexcept {
    impl()->Advance(1);
    return *impl();
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation &
base_vector_iterator<vector_element, vector_iterator_implementation>::operator--() noexcept {
    impl()->Advance(-1);
    return *impl();
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation
base_vector_iterator<vector_element, vector_iterator_implementation>::operator++(int) noexcept {
    vector_iterator_implementation copy = *impl();
    ++(*this);
    return copy;
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation
base_vector_iterator<vector_element, vector_iterator_implementation>::operator--(int) noexcept {
    vector_iterator_implementation copy = *impl();
    --(*this);
    return copy;
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation &
base_vector_iterator<vector_element, vector_iterator_implementation>::operator+=(difference_type a) noexcept {
    impl()->Advance(a);
    return *impl();
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation &
base_vector_iterator<vector_element, vector_iterator_implementation>::operator-=(difference_type a) noexcept {
    impl()->Advance(-a);
    return *impl();
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation
base_vector_iterator<vector_element, vector_iterator_implementation>::operator+(difference_type a) noexcept {
    vector_iterator_implementation copy = *impl();
    copy += a;
    return copy;
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr vector_iterator_implementation
base_vector_iterator<vector_element, vector_iterator_implementation>::operator-(difference_type a) noexcept {
    vector_iterator_implementation copy = *impl();
    copy -= a;
    return copy;
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr typename base_vector_iterator<vector_element, vector_iterator_implementation>::difference_type
base_vector_iterator<vector_element, vector_iterator_implementation>::operator-(
        const vector_iterator_implementation &other) const noexcept {
    return impl()->Difference(other);
}

template<typename vector_element, typename vector_iterator_implementation>
constexpr void base_vector_iterator<vector_element, vector_iterator_implementation>::swap(
        vector_iterator_implementation &other) noexcept {
    std::swap(**this, *other);
}


template<typename vector_element>
constexpr _forward_iterator<vector_element>::_forward_iterator(vector_element *pt) noexcept
        :base_vector_iterator<vector_element, _forward_iterator<vector_element>>(pt) {}

template<typename vector_element>
inline constexpr void _forward_iterator<vector_element>::Advance(std::ptrdiff_t a) noexcept {
    this->pt += a;
}

template<typename vector_element>
inline constexpr std::ptrdiff_t
_forward_iterator<vector_element>::Difference(const _forward_iterator &other) const noexcept {
    return this->pt - other.pt;
}

template<typename vector_element>
constexpr _reverse_iterator<vector_element>::_reverse_iterator(vector_element *pt) noexcept
        :base_vector_iterator<vector_element, _reverse_iterator<vector_element>>(pt) {}

template<typename vector_element>
inline constexpr void _reverse_iterator<vector_element>::Advance(std::ptrdiff_t a) noexcept {
    this->pt -= a;
}

template<typename vector_element>
inline constexpr std::ptrdiff_t
_reverse_iterator<vector_element>::Difference(const _reverse_iterator &other) const noexcept {
    return -(this->pt - other.pt);
}

template<typename vector_element>
constexpr _forward_iterator<vector_element> _reverse_iterator<vector_element>::base() const noexcept {
    return _forward_iterator(this->pt - 1);
}

template<typename vector_element>
constexpr _reverse_iterator<vector_element>::_reverse_iterator(const _forward_iterator<vector_element> &it) noexcept
        :_reverse_iterator(it.pt + 1) {}

#endif //VEC_ITERATOR_H
