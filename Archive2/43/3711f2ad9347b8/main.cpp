#include <iostream>

void
c_api(void (*fun)(void*), void* data) {
    fun(data);
}

template <typename F>
void
call_c(void (*c)(void (*)(void*), void*), F&& f) {
    struct closure {
        F&& fun;
        static void
        trampoline(void* ptr) {
            static_cast<closure*>(ptr)->fun();
        }
    } t{std::move(f)};
    c(&closure::trampoline, &t);
}

int
main() {
    int i = 5;
    call_c(&c_api, [&] { std::cout << i; });
}
