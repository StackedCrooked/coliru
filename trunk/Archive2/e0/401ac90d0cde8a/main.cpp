#include <utility>

struct foo {
    foo& operator=(foo const&) = delete;
};
 
template <typename T>
struct wrapper {};

wrapper<decltype(std::declval<foo>() = std::declval<foo>())> x;

int main () {}