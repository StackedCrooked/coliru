#include <cstdint>
#include <iostream>
#include <iterator>
#include <boost/iterator/iterator_facade.hpp>

// D-style forward range, does not consume input
class DArrayRange
{
public:
    template<int N> 
    explicit DArrayRange(int (&a)[N]): b_{a}, e_{a+N} {}
    
    bool empty() { return b_ == e_; }
    void pop_front() { ++b_; }
    int front() const { return *b_; }
private:
    int *b_, *e_;    
};

// D-style input range, consumes input
class DBitRange
{
public:
    explicit DBitRange(uint64_t& b): b_{b} {}
    
    bool empty() { return b_ == 0; }
    void pop_front() { b_ &= b_ - 1; }
    int front() const { return __builtin_ctzll(b_); }    
private:
    uint64_t& b_;
};

class CPPBitRange
{
public:
    explicit CPPBitRange(uint64_t& b): b_{b} {}
    
    struct iterator : boost::iterator_facade<iterator, int, std::input_iterator_tag, int> {
        iterator(CPPBitRange* rng) : rng{rng} {}
        
        int dereference() const { return __builtin_ctzll(rng->b_); }
        void increment() { rng->b_ &= rng->b_ - 1; }
        bool equal(const iterator& other) const {
            return rng ? (other.rng || rng->b_ == 0) : (!other.rng || other.rng->b_ == 0);
        }
        CPPBitRange* rng;
    };
    
    iterator begin() { return this; }
    iterator end() { return nullptr; }
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
    for (auto b: CPPBitRange{primes})
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
    
    // C-style iteration over array
    for (auto b = std::begin(vals), e = std::end(vals); b != e; ++b)
        std::cout << *b << ", ";
    std::cout << "\n"; 

    // D-style iteration over array
    // translates 1-on-1 to C code
    for (auto valrange = DArrayRange{vals}; !valrange.empty(); valrange.pop_front())
        std::cout << valrange.front() << ", ";
    std::cout << "\n";

    // C++ range-based for iteration over array
    // also translates 1-on-1 to C code
    // but it is a leaky abstraction because
    // [stmt.ranged]/1 *mandates* a C-style implementation
    for (auto v: vals)
        std::cout << v << ", ";
    std::cout << "\n";

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
