#ifdef DEUBG
#define _GLIBCXX_DEBUG
#endif

#include <array>

int main()
{
    std::array<int, 1> a = { 0 };
    return a[1];
}