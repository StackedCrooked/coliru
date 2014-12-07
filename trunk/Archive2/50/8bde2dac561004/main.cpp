#include <cstddef>
void foo(const char*) {}
template<std::size_t N>
void foo(char (&a)[N]) = delete;

int main()
{
    // wait, what?
    foo("lol");
} 