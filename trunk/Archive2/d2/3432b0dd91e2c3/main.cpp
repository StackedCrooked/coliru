#include <iostream>
#include <type_traits>

template<typename T>
void bar(T t)
{
    static_assert(std::is_same<T, const int>::value, "Error!");
    std::cout << t << '\n';
}

int main()
{
    //  static_assert doesn't fire because T==const int
    bar<const int>(1);

    //  But here static_assert fires bacause T==int (see the error message). Why is this?
    //  If I replace `bar` by `bar<const int>` below the code compiles.

    void(*pf)(int) = bar;
    pf(1000);
}