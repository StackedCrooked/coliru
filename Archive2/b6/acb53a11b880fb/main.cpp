#include <cstdint>
#include <iostream>
#include <iterator>
#include <boost/iterator/iterator_facade.hpp>

template <typename CRTP, typename ValueType>
class DInputRange
{
public:
    struct iterator : boost::iterator_facade<iterator, ValueType, std::input_iterator_tag, ValueType> {
        CRTP* rng;

        iterator(CRTP* rng) : rng{rng} {}
        
        auto dereference() const -> decltype(rng->front()) { return rng->front(); }
        void increment() { rng->pop_front(); }
        bool equal(const iterator& other) const {
            return rng ? (other.rng || rng->empty()) : (!other.rng || other.rng->empty());
        }
    };

    iterator begin() { return static_cast<CRTP*>(this); }
    iterator end() { return nullptr; }
};

// D-style input range, consumes input
class DBitRange : public DInputRange<DBitRange, int>
{
public:
    explicit DBitRange(uint64_t& b): b_{b} {}
    
    bool empty() { return b_ == 0; }
    void pop_front() { b_ &= b_ - 1; }
    int front() const { return __builtin_ctzll(b_); }    
private:
    uint64_t& b_;
};

void C_style(uint64_t primes) {
    for (; primes != 0; primes &= primes - 1)
        std::cout << __builtin_ctzll(primes) << ", ";
    std::cout << "\n";        
}

void D_style(uint64_t primes) {
    for (auto bitrange = DBitRange{primes}; !bitrange.empty(); bitrange.pop_front())
        std::cout << bitrange.front() << ", ";
    std::cout << "\n";
}

void CPP_style(uint64_t primes) {
    for (auto b: DBitRange{primes})
        std::cout << b << ", ";
    std::cout << "\n";
}

#if 0
int main()
{
    int vals[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61 };
    uint64_t primes = 0;
    for (auto v: vals)
        primes ^= uint64_t{1} << v;
    
    // C-style iteration over bitmap
    for (auto bitmap = primes; bitmap != 0; bitmap &= bitmap - 1)
        std::cout << __builtin_ctzll(bitmap) << ", ";
    std::cout << "\n";        
    
    // D-style iteration over bitmap
    // translates 1-on-1 to C code, no proxy iterators and references
    for (auto bitrange = DBitRange{primes}; !bitrange.empty(); bitrange.pop_front())
        std::cout << bitrange.front() << ", ";
    std::cout << "\n";

    // CHALLENGE: define C++ range-based for iteration over bitmap
    // that translates 1-on-1 into the equivalent C/D code
    for (auto b: CPPBitRange{primes})
        std::cout << b << ", ";
    std::cout << "\n";
}
#endif
