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

int main()
{
    printf("%u\n", "blah"_djb);
    return 0;
}