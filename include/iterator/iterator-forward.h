#ifndef VEC_ITERATOR_FORWARD_H
#define VEC_ITERATOR_FORWARD_H
#include <cstddef>
#include <compare>
#include <iterator>
template <typename vector_element, typename vector_iterator_implementation>
struct base_vector_iterator{
    using selftype = base_vector_iterator<vector_element,vector_iterator_implementation>;
    using value_type = vector_element;
    using difference_type = std::ptrdiff_t;
    using pointer = vector_element*;
    using reference = vector_element&;
    using category = std::random_access_iterator_tag;
explicit constexpr base_vector_iterator(vector_element* pt) noexcept;
[[nodiscard]] constexpr reference operator*() noexcept;
[[nodiscard]] constexpr const reference operator*() const noexcept;
[[nodiscard]] constexpr std::strong_ordering operator<=>(const vector_iterator_implementation& other) const noexcept;
[[nodiscard]] constexpr bool operator==(const vector_iterator_implementation& other) const noexcept;
[[nodiscard]] constexpr bool operator!=(const vector_iterator_implementation& other) const noexcept;
constexpr vector_iterator_implementation& operator++() noexcept;
constexpr vector_iterator_implementation operator++(int) noexcept;
constexpr vector_iterator_implementation& operator--() noexcept;
constexpr vector_iterator_implementation operator--(int) noexcept;
constexpr vector_iterator_implementation& operator+=(difference_type a) noexcept;
constexpr vector_iterator_implementation operator+(difference_type a) noexcept;
constexpr vector_iterator_implementation& operator-=(difference_type a) noexcept;
constexpr vector_iterator_implementation operator-(difference_type a) noexcept;
[[nodiscard]] constexpr difference_type operator-(const vector_iterator_implementation& other) const noexcept;
constexpr void swap(vector_iterator_implementation& other) noexcept;

protected:
    vector_element* pt;
private:
    [[nodiscard]] inline constexpr const vector_iterator_implementation* impl() const noexcept;
    [[nodiscard]] inline constexpr vector_iterator_implementation* impl() noexcept;
};

template <typename vector_element>
struct _forward_iterator : public base_vector_iterator<vector_element, _forward_iterator<vector_element>>{
    using value_type = vector_element;
    using difference_type = std::ptrdiff_t;
    using pointer = vector_element*;
    using reference = vector_element&;
    using category = std::random_access_iterator_tag;
    constexpr explicit _forward_iterator(vector_element * pt) noexcept;
private:
   inline constexpr void Advance(difference_type) noexcept;
    [[nodiscard]] inline constexpr difference_type Difference(const _forward_iterator& other) const noexcept;
    friend base_vector_iterator<vector_element,_forward_iterator<vector_element>>;
};
template <typename vector_element>
struct _reverse_iterator : public base_vector_iterator<vector_element, _reverse_iterator<vector_element>>{
    using value_type = vector_element;
    using difference_type = std::ptrdiff_t;
    using pointer = vector_element*;
    using reference = vector_element&;
    using category = std::random_access_iterator_tag;
    constexpr explicit _reverse_iterator(vector_element * pt) noexcept;
    constexpr explicit _reverse_iterator(const _forward_iterator<vector_element>& it) noexcept;
    [[nodiscard]] constexpr _forward_iterator<vector_element> base() const noexcept;
private:
    inline constexpr void Advance(difference_type) noexcept;
    [[nodiscard]] inline constexpr difference_type Difference(const _reverse_iterator& other) const noexcept;
    friend base_vector_iterator<vector_element,_reverse_iterator<vector_element>>;
};
#endif //VEC_ITERATOR_FORWARD_H
