#include <cstddef>
#include <iterator>
#include <stdexcept>

template<typename T>
class array_ref {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;
    using iterator = T*;
    using const_iterator = T const*;
    using reverse_iterator = std::reverse_iterator<T*>;
    using const_reverse_iterator = std::reverse_iterator<T const*>;

    template<typename U>
    array_ref(U&& array) : data_(array.data()), size_(array.size()) { }

    T* begin() const {
        return data_;
    }

    T* end() const {
        return data_ + size_;
    }

    T const* cbegin() const {
        return data_;
    }

    T const* cend() const {
        return data_ + size_;
    }

    T* data() const {
        return data_;
    }

    std::size_t size() const {
        return size_;
    }

    T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range(__func__);
        }
        return data_[index];
    }

private:
    T* data_;
    std::size_t size_;
};

// example:
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

void f(array_ref<int> xs) {
    std::cout << std::accumulate(xs.begin(), xs.end(), 0) << '\n';
}

int main() {
    f(std::vector<int>{1, 2, 3, 4});
    f(std::array<int, 4>{{1, 2, 3, 4}});
    return 0;
}