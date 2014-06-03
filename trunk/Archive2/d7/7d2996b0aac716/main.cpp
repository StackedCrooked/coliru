#include <stdio.h>
#include <utility>

template<typename _Ret, typename... Args, typename... Parameters>
static _Ret call(_Ret (*fp)(Args...), Parameters &&... params)
{
    return fp(std::forward<Parameters>(params)...);
}

int foo(int arr[4])
{
    printf("arr: %i,%i,%i,%i\n", arr[0], arr[1], arr[2], arr[3]);
    return 0;
}

int main()
{
    int arr[4] = { 1, 2, 3, 4 };
    call(&foo, arr);
    call(&foo, &arr[0]);

    return 0;
}
