#include <cstdint>
#include <iostream>

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
    //for (auto b: primes)
    //    std::cout << b << ", ";
    //std::cout << "\n";
}
