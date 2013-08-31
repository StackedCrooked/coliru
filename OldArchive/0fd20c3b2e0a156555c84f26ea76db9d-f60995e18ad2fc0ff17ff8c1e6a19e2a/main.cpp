#include <cstdio>
#include <cstddef>

constexpr unsigned int operator"" _djb(const char* const str, std::size_t len)
{
    return len ? str[0] + (33 * ::operator"" _djb(str+1, len-1)) : 5381;
}

constexpr unsigned int x = "blah"_djb;

template <unsigned int>
struct foo {};

foo<"blah"_djb> bar;

static_assert("blah"_djb == 2090320348, "let's hope the hardcoded hash is correct"); // see, evaluated at compile-time

int main()
{
    printf("%u\n", "blah"_djb);
    return 0;
}