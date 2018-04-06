#ifndef RAY_VECTOR_HPP
#define RAY_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <iterator>
#include <limits>
#include <utility>

namespace rays {

template <typename T>
class Vector {
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

    std::unique_ptr<T[]> storage;
    size_type storage_size     = 0;
    size_type storage_max_size = 0;

public:
    Vector() = default;
    Vector(const size_type count, const T &value = T())
        : storage_size(count),
          storage_max_size(count),
          storage(std::make_unique<T[]>(count))
    {
        fill(value);
    }

    T &operator[](const size_type index) noexcept { return storage[index]; }
    T &at(const size_type index)
    {
        if (index < storage_size) {
            return storage[index];
        } else {
            throw std::out_of_range("Index is larger than size of array!");
        }
    }

    void fill(const T &value)
    {
        std::fill(std::begin(&storage), std::end(&storage + storage_size),
                  value);
    }

    void swap(Vector &other)
    {
        for (size_type i = 0; i < storage_size; ++i) {
            std::swap(storage[i], other.storage[i]);
        }
    }

    [[nodiscard]] bool empty() const noexcept { return storage_size == 0; }

    auto max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max();
    }
    auto size() const noexcept { return storage_size; }
    auto capacity() const noexcept { return storage_max_size; }

    auto reserve(const size_type new_cap)
    {
        if (new_cap > storage_max_size) {
            auto newStorage = std::make_unique<T[]>(new_cap);
            for (size_type i = 0; i < storage_size; ++i) {
                newStorage[i] = storage[i];
            }
            std::exchange(storage, newStorage);
        }
    }

    auto shrink_to_fit()
    {
        if (storage_size < storage_max_size) {
            auto newStorage = std::make_unique<T[]>(storage_size);
            for (size_type i = 0; i < storage_size; ++i) {
                newStorage[i] = storage[i];
            }
            std::exchange(storage, newStorage);
        }
    }

    auto clear() noexcept { storage_size = 0; }

    auto push_back(T value)
    {
        if (storage_size + 1 == storage_max_size) {
            auto newStorage = std::make_unique<T[]>((storage_size + 1) * 2);
            for (size_type i = 0; i < storage_size; ++i) {
                newStorage[i] = storage[i];
            }
            std::exchange(storage, newStorage);
        }

        storage[storage_size] = value;
        ++storage_size;
    }

    auto pop_back() { std::exchange(storage[storage_size--], T{}); }
    auto resize(const size_type count)
    {
        if (count <= storage_size) {
            return;
        }

        if (count > storage_max_size) {
            auto newStorage = std::make_unique<T[]>(count);
            for (size_type i = 0; i < storage_size; ++i) {
                newStorage[i] = storage[i];
            }
            std::exchange(storage, newStorage);
        } else {
            storage_size = count;
        }
    }

    T &front() const noexcept { return storage[0]; }
    T &front() noexcept { return storage[0]; }
    T &back() const noexcept { return storage[storage_size - 1]; }
    T &back() noexcept { return storage[storage_size - 1]; }

    T *data() noexcept { return &storage; }
    const T *data() const noexcept { return &storage; }

    iterator begin() noexcept { return &storage[0]; }
    iterator end() noexcept { return &storage[storage_size]; }
    const_iterator cbegin() const noexcept { return &storage[0]; }
    const_iterator cend() const noexcept { return &storage[storage_size]; }

    iterator rbegin() noexcept { return &storage[storage_size - 1]; }
    iterator rend() noexcept { return &storage[0] - 1; }
    const_iterator crbegin() const noexcept
    {
        return &storage[storage_size - 1];
    }
    const_iterator crend() const noexcept { return &storage[0] - 1; }
};
}  // namespace rays

#endif
