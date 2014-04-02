#include <iterator>
#include <memory>

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long
         >
class indexer : public std::iterator<std::random_access_iterator_tag, T, Difference>
{
    using Indexer = indexer<C, T, Index, Difference>;
public:
    indexer(C<T>& c, Index i, Index end)
        : c_(std::addressof(c)), i_(i), end_(end) {}

    T& operator*() const {
        return (*c_)[i_];
    };
    
    T& operator[](Index i) const {
        return (*c_)[i_ + i];
    }

    Indexer& operator++() {
        ++i_;
        return *this;
    };
    
    Indexer operator++(int) {
        auto&& old = *this;
        operator++();
        return old;
    }
    
    Indexer& operator--() {
        --i_;
        return *this;
    }
    
    Indexer operator--(int) {
        auto&& old = *this;
        operator--();
        return old;
    }
    
    Indexer& operator+=(Index delta) {
        i_ += delta;
        return *this;
    }
    
    Indexer operator-=(Index delta) {
        i_ -= delta;
        return *this;
    }
    
    Difference operator-(Indexer const& other) const {
        return (Difference)i_ - other.i_;
    }

    bool operator==(Indexer const& other) const {
        return i_ == other.i_;
    }
    
    bool operator<(Indexer const& other) const {
        return i_ < other.i_;
    }

private:
    C<T>* c_;
    Index i_, end_;
};

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long,
         typename Delta,
         typename Indexer = indexer<C, T, Index, Difference>
         >
Indexer operator+(indexer<C, T, Index, Difference> lhs, Delta rhs) {
    return lhs += rhs;
}

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long,
         typename Delta,
         typename Indexer = indexer<C, T, Index, Difference>
         >
Indexer operator+(Delta lhs, indexer<C, T, Index, Difference> rhs) {
    return rhs += lhs;
}

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long,
         typename Delta,
         typename Indexer = indexer<C, T, Index, Difference>
         >
Indexer operator-(indexer<C, T, Index, Difference> lhs, Delta rhs) {
    return lhs -= rhs;
}

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long,
         typename Delta,
         typename Indexer = indexer<C, T, Index, Difference>
         >
Indexer operator-(Delta lhs, indexer<C, T, Index, Difference> rhs) {
    return rhs -= lhs;
}

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long
         >
bool operator!=(indexer<C, T, Index, Difference> const& lhs, indexer<C, T, Index, Difference> const& rhs) {
    return !(lhs == rhs);
}

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long
         >
bool operator>(indexer<C, T, Index, Difference> const& lhs, indexer<C, T, Index, Difference> const& rhs) {
    return rhs < lhs;
}

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long
         >
bool operator<=(indexer<C, T, Index, Difference> const& lhs, indexer<C, T, Index, Difference> const& rhs) {
    return !(lhs > rhs);
}

template<template<typename> class C,
         typename T,
         typename Index = std::size_t,
         typename Difference = long
         >
bool operator>=(indexer<C, T, Index, Difference> const& lhs, indexer<C, T, Index, Difference> const& rhs) {
    return !(lhs < rhs);
}

#include <algorithm>
#include <iostream>
#include <vector>

template<typename T>
class vector_view
{
public:
    vector_view(std::vector<T>& v, std::size_t start, std::size_t n)
        : v_(v), start_(start), n_(n) {}

    std::size_t size() { return n_; }
    T& operator[](int i) { return v_[start_ + i]; }

private:
    std::vector<T>& v_;
    std::size_t start_, n_;
};

template<typename T>
indexer<vector_view, T> begin(vector_view<T>& vv) {
    return indexer<vector_view, T>(vv, 0, vv.size());
}

template<typename T>
indexer<vector_view, T> end(vector_view<T>& vv) {
    auto&& size = vv.size();
    return indexer<vector_view, T>(vv, size, size);
}

int main() {
    std::vector<int> v = {0, 6, 1, 5, 3, 8};
    
    /* double the three elements starting from the 2nd element (i.e. v[2], v[3], v[4]) */
    for (auto& x : vector_view<int>(v, 2, 3))
        x *= 2;

    for (auto x : v)
        std::cout << x << ' ';
    std::cout << std::endl;
    
    vector_view<int> vv(v, 3, 3);
    /* sort the three elements starting from the 3rd element */
    std::sort(begin(vv), end(vv));
    
    for (auto x : v)
        std::cout << x << ' ';
    std::cout << std::endl;
    
    return 0;
}
