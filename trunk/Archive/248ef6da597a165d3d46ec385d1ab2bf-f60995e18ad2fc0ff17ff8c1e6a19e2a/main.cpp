#include <cstdio>
#include <cstddef>

unsigned int operator"" _djb(const char* const str, std::size_t len)
{
    printf("%d\n", __builtin_constant_p(str));
    return len ? str[0] + (33 * ::operator"" _djb(str+1, len-1)) : 5381;
}

int main()
{
    printf("%u\n", "blah"_djb);
    return 0;
}