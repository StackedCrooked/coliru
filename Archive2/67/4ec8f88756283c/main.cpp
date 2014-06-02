#include <cstdio>
#include <utility>

template<typename _Ret, typename... Args>
static auto call(_Ret (*fp)(Args...), Args &&... args) {
    return fp(std::forward<Args>(args)...);
}

int foo(int (&arr)[4]) {
    printf("arr: %i,%i,%i,%i\n", arr[0], arr[1], arr[2], arr[3]);
    return 0;
}

int main() {
    int arr[4] = { 1, 2, 3, 4 };
    call(foo, arr);
}
