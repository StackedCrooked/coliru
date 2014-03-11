#include <map>
#include <iostream>
#include <string>

template < typename F, typename... Ts > 
void foo( F&& f, Ts&&.. ts ) {
    std::forward<F>(f)(std::forward<Ts>(ts))...;
}
int main() {
    auto f = []( auto const & v ) { std::cout << v << " "; }
    foo(1, 3.5, std::string{"uieuie"});
}