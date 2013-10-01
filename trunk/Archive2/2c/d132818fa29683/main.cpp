#include <iostream>

unsigned constexpr const_hash(char const *input)
{
    return input[0] ? 33 * const_hash(input + 1) + input[0] : 5381;
}

unsigned constexpr const_hash_v2(char const *input, unsigned prev = 5381)
{
    return input[0] ? const_hash_v2(input + 1, 33 * prev + input[0]) : prev;
}

int main()
{
    static_assert(const_hash("abc") == const_hash_v2("cba"), "");
}