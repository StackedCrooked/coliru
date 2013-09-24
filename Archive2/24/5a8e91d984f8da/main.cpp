#include <cstdio>

template<typename T>
void print(T a, T b) {
    printf("%d x %d\n", a, b);
}

template<typename T>
void product_printer(T head) {
}

template<typename T, typename... Ts>
void product_printer(T head, T matched, Ts... tail) {
    print(head, matched);
    product_printer(head, tail...);
}

template<typename T, typename... Ts>
void product_impl(int count, T head, Ts... tail) {
    if (count == 0) { return; } // Tail won't ever be empty so we have to know when to stop
    product_printer(head, head, tail...);
    product_impl(count - 1, tail..., head);
}

template<typename... Ts>
void product(Ts... tail) {
    product_impl(sizeof...(tail), tail...);
}

void product() {}

int main()
{
    product(1, 2, 3, 4, 5);
    return 0;
}