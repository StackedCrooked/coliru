#include <cstddef>
#include <iterator>
#include <memory>
#include <utility>

template<typename T, typename Category>
class any_iterator : public std::iterator<Category, T, std::ptrdiff_t, T*, T&> {
public:
    template<typename I>
    any_iterator(I iterator)
        : ptr(new derived<I>(std::move(iterator))) { }

    any_iterator(any_iterator const& other)
        : ptr(other.ptr->clone()) { }

    any_iterator& operator=(any_iterator other) {
        swap(ptr, other.ptr);
    }

private:
    struct base {
        virtual ~base() = default;

        virtual base* clone() const = 0;
    };

    template<typename I>
    struct derived {
        explicit derived(I iterator)
            : iterator(std::move(iterator)) { }

        base* clone() const override {
            return new derived(iterator);
        }

        I iterator;
    };

    std::unique_ptr<base> ptr;
};

// example:
#include <iostream>
#include <numeric>
#include <vector>

int f(any_iterator<int, std::input_iterator_tag> begin, any_iterator<int, std::input_iterator_tag> end) {
    return std::accumulate(begin, end, 0);
}

int main() {
    std::vector<int> xs{1, 2, 3};
    std::cout << f(xs.begin(), xs.end());
    return 0;
}