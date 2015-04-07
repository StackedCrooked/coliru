#include <tuple>
#include <functional>

char x[] = "lmao";

decltype(auto)
f(const char* x)
{
    return std::make_tuple (x, x);
}

int main()
{
    char* i;
    char* a;
    std::tie(i, a) = f("foo");
    printf("%s %c", i, a[0]);
    return 0;
}