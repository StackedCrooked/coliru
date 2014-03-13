#include <type_traits>

int main()
{
    static_assert(not std::is_same<char, unsigned char>(), "trolol");
    static_assert(not std::is_same<char, signed char>(), "thank ansi C");
}