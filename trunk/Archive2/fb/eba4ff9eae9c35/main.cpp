#include <type_traits>


template<unsigned N>
void brief(const char (&)[N], typename std::enable_if<(N < 10)>::type* = 0) {}

int main()
{
    brief("abc");
    brief("abcdefghijklmnopqr"); // not brief enough
}
