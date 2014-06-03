#include <stdio.h>
#include <cstdlib>
#include <utility>
#include <type_traits>

template<typename _Ret, typename... Args>
static _Ret call(_Ret (*fp)(Args...), Args &&... args)
{
    return fp(std::forward<Args>(args)...);
}

template<std::size_t N>
int foo(int (&arr)[N])
{
    printf("arr: ");
    for(auto i : arr) {
        printf("%i,", i);
    }
    printf("\n");
    return 0;
}

int main(int, char**)
{
    int arr[4] = { 1, 2, 3, 4 };
    
    call(foo<std::extent<decltype(arr)>::value>, arr);
}
