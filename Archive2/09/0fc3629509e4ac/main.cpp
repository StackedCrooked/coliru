#include <iomanip>
#include <iostream>
#include <locale>

constexpr unsigned long long fibo_(unsigned n, unsigned long long prev, unsigned long prevprev) {
    return n == 0 ? prev : fibo_(n - 1, prev + prevprev, prev);
}   
constexpr unsigned long long fibo(unsigned n) {
    return (n < 2) ? 1 : fibo_(n - 1, 1, 1);
}   
unsigned long long fiboiter(unsigned n, unsigned long long &prev, 
                            unsigned long long &prevprev) {
    return prev = (n < 2) ? prevprev = 1 : 
        (std::swap(prev, prevprev), prev + prevprev);
}    
constexpr unsigned max_fibo(unsigned n) {
    return (fibo(n+1) >= fibo(n)) ? max_fibo(n+1) : n;
}    
const unsigned MAX_FIBO_TERM = max_fibo(0);

int main(int argc, char **)
{
    // format numeric output according to user's preferred locale
    std::cout.imbue(std::locale{""});
    unsigned long long prev, prevprev;

    if (argc > 1) {
        for (unsigned i = 0; i <= MAX_FIBO_TERM; ++i) 
            std::cout << "fib(" << std::setw(2) << i << ") = " 
                      << std::setw(26) << fiboiter(i, prev, prevprev) << '\n';
    } else {
        for (unsigned i = 0; i <= MAX_FIBO_TERM; ++i) 
            std::cout << "fib(" << std::setw(2) << i << ") = " 
                      << std::setw(26) << fibo(i) << '\n';
    }
}
