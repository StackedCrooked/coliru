#include <iterator>
#include <type_traits>
#include <iostream>

template<typename T, bool Infinite = false>
struct numeric_range_iterator : std::iterator<std::bidirectional_iterator_tag, T> {
    using difference_type = typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type;
    T current;
    difference_type step;
    numeric_range_iterator(): current(0), step(1) {}
    numeric_range_iterator(T t, difference_type s = 1): current(t), step(s) {}

    T operator*() const { 
        return current;
    }

    const T* operator->() const {
        return &current;
    }

    auto operator++() -> decltype(*this) {
        current += step;
        return *this;
    }

    numeric_range_iterator operator++(int) {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    auto operator--() -> decltype(*this) {
        current -= step;
        return *this;
    }

    numeric_range_iterator operator--(int) {
        auto copy = *this;
        --(*this);
        return copy;
    }

    bool operator!=(const numeric_range_iterator& other) const {
        return Infinite ? true : other.current != current;
    }

    bool operator==(const numeric_range_iterator& other) const {
        return Infinite ? false : other.current == current;
    }
};

template<typename T, bool Infinite = false>
struct numeric_range {
public:
    using value_type = T;
    using iterator = numeric_range_iterator<T, Infinite>;
    using const_iterator = const iterator;
    using difference_type = typename iterator::difference_type;
private:
    iterator first;
    iterator last;
public:
    static_assert(std::is_integral<T>(), "numeric_range must be integral types only");
    numeric_range() {}
    numeric_range(T begin): first(begin) {}
    numeric_range(T begin, T end): first(begin), last(end) {
        static_assert(!Infinite, "Cannot define an end to an infinite range");
    }

    numeric_range(T begin, T end, difference_type step): first(begin, step), last(end, step) {
        static_assert(!Infinite, "Cannot define an end to an infinite range");
    }

    auto step(difference_type t) -> decltype(*this) {
        first.step = t;
        last.step = t;
        return *this;
    }

    iterator begin() const {
        return first;
    }

    iterator end() const {
        return last;
    }

    constexpr bool infinite() const {
        return Infinite;
    }

    bool empty() const {
        return first == last;
    }

    void pop_back() {
        static_assert(!Infinite, "Cannot pop_back an infinite range");
        if(empty())
            return;
        --last;
    }

    void push_back(T t) {
        static_assert(!Infinite, "Cannot push_back an infinite range");
        last = iterator(t);
    }

    void pop_front() {
        if(empty())
            return;
        ++first;
    }

    auto front() const -> decltype(*first) {
        return *first;
    }

    auto back() const -> decltype(*last) {
        static_assert(!Infinite, "Cannot receive the last element of an infinite range");
        return *last;
    }

    size_t size() const {
        static_assert(!Infinite, "Infinite ranges do not have length");
        return std::distance(first, last);
    }
};

template<typename T>
numeric_range<T, true> irange(T begin) {
    return {begin};
}

template<typename T, typename R = numeric_range<T>>
R irange(T begin, T end) {
    return end >= begin ? R{begin, end} : R{begin, end, -1};
}

int main() {
    auto range = irange('z','a');
    range.pop_back();
    range.pop_front();
    std::cout << range.size() << '\n';
    for(auto&& i : irange('a')) {
        std::cout << i << ' ';
        if(i == 'z')
            break;
    }
    std::cout << '\n';
    for(auto&& i : range) {
        std::cout << i << ' ';
    }
}