#include <iostream>

template<class Type>
class range {
public:
    class iterator {
    public:
        iterator(const Type& x)
            : i(x)
            {}
        iterator& operator++(int) { ++i; return (*this); }
        iterator operator++() { iterator tmp = (*this); ++i; return tmp; }
        const Type& operator*() const { return i; }
        bool operator==(const iterator& o) const { return o.i == i; }
        bool operator!=(const iterator& o) const { return !(o == (*this)); }
    private:
        Type i;
    };
    range(const Type& x, const Type& y)
        : a(x)
        , b(y)
        {}
    iterator begin() const  { return iterator(a); }
    iterator end() const    { return iterator(b); }
private:
    const Type a;
    const Type b;
};

auto main() -> int {
    for (auto i : range<int>(0, 10))
        std::cout << i;
}