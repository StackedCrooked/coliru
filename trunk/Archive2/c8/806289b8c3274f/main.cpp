#include <stdio.h>
#include <utility>

template<typename _Ret, typename... Args>
static _Ret call(_Ret (*fp)(Args&&...), Args &&... args)
{
    return fp(std::forward<Args>(args)...);
}

template<typename _Ret, typename... Params, typename... Args>
static _Ret call1(_Ret (*fp)(Params&&...), Args &&... args)
{
    return fp(std::forward<Args>(args)...);
}

int foo(int *&& arr)
{
    printf("arr: %i,%i,%i,%i\n", arr[0], arr[1], arr[2], arr[3]);
    return 0;
}

int main(int, char**)
{
    int arr[4] = { 1, 2, 3, 4 };
    call(foo, &arr[0]);
    call1(foo, &arr[0]);

    return 0;
}
