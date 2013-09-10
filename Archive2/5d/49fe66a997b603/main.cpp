#include <vector>
int main()
{
    struct { int i; } a[] = { { 42 }, { 0 } };
    std::vector<std::remove_reference<decltype(*a)>::type> v(4);

    return v[0].i == a[1].i? 1 : 2;
}
