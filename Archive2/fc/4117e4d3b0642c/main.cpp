#include <iostream>

constexpr bool equal( const char * a, const char * b ) {
    if (!a || !b)
        return false;
    while ( *a && *b && *a == *b ) {
        ++a; ++b;
    }
    return !*a && !*b;
}

constexpr const char * a = "toto";
constexpr const char * b = "totvvv";
constexpr auto c = equal(a,b);
constexpr auto d = equal(a,a);

int main() {
  std::cout << c << std::endl;
  std::cout << d << std::endl;
}