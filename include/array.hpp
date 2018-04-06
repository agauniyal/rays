#ifndef RAY_ARRAY_HPP
#define RAY_ARRAY_HPP

#include <stdexcept>
#include <type_traits>

namespace rays {

template <typename T, std::size_t storage_size>
class Array {
    T storage[storage_size];

    using value_type             = T;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type &;
    using const_reference        = const value_type &;
    using pointer                = value_type *;
    using const_pointer          = const value_type *;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
    constexpr T &operator[](const size_type index) noexcept
    {
        return storage[index];
    }
    constexpr T &at(const size_type index)
    {
        if (index < storage_size) {
            return storage[index];
        } else {
            throw std::out_of_range("Index is larger than size of array!");
        }
    }

    void fill(const T &value)
    {
        for (size_type i = 0; i < storage_size; ++i) {
            storage[i] = value;
        }
    }

    void swap(Array &other) noexcept(std::is_nothrow_swappable<T>::value)
    {
        for (size_type i = 0; i < storage_size; ++i) {
            std::swap(storage[i], other.storage[i]);
        }
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return storage_size == 0;
    }

    constexpr auto max_size() const noexcept { return storage_size; }

    constexpr auto size() const noexcept { return storage_size; }

    constexpr T &front() const noexcept { return storage[0]; }
    constexpr T &front() noexcept { return storage[0]; }
    constexpr T &back() const noexcept { return storage[storage_size - 1]; }
    constexpr T &back() noexcept { return storage[storage_size - 1]; }

    constexpr T *data() noexcept { return &storage; }
    constexpr const T *data() const noexcept { return &storage; }

    constexpr iterator begin() noexcept { return &storage[0]; }
    constexpr iterator end() noexcept { return &storage[storage_size]; }
    constexpr const_iterator cbegin() const noexcept { return &storage[0]; }
    constexpr const_iterator cend() const noexcept
    {
        return &storage[storage_size];
    }

    constexpr iterator rbegin() noexcept { return &storage[storage_size - 1]; }
    constexpr iterator rend() noexcept { return &storage[0] - 1; }
    constexpr const_iterator crbegin() const noexcept
    {
        return &storage[storage_size - 1];
    }
    constexpr const_iterator crend() const noexcept { return &storage[0] - 1; }
};
}  // namespace rays

#endif
