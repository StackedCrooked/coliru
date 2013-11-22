#include <iostream>
#include <stdexcept>
 
// constexpr functions use recursion rather than iteration
constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n-1));
}
 
// literal class
class conststr {
    const char * p;
    std::size_t sz;
 public:
    template<std::size_t N>
    constexpr conststr(const char(&a)[N]) : p(a), sz(N-1) {}
    // constexpr functions signal errors by throwing exceptions from operator ?:
    constexpr char operator[](std::size_t n) const {
        return n < sz ? p[n] : throw std::out_of_range("");
    }
    constexpr std::size_t size() const { return sz; }
};
 
constexpr std::size_t countlower(conststr s, std::size_t n = 0,
                                             std::size_t c = 0) {
    return n == s.size() ? c :
           s[n] >= 'a' && s[n] <= 'z' ? countlower(s, n+1, c+1) :
           countlower(s, n+1, c);
}
 
// output function that requires a compile-time constant, for testing
template<int n> struct constN {
    constN() { std::cout << n << '\n'; }
};
 
int main()
{
    std::cout << "4! = " ;
    constN<factorial(4)> out1; // computed at compile time
 
     int k = 8; // disallow optimization using volatile
    std::cout << k << "! = " << factorial(k) << '\n'; // computed at run time
 
    std::cout << "Number of lowercase letters in \"Hello, world!\" is__";
    constN<countlower("Helo, world!")> out2; // implicitly converted to conststr
}