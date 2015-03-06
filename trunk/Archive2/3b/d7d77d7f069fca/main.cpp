#include <iostream>

bool once() {
    thread_local static int do_once = 0;
    return do_once++ % 2 == 0;
}
#define with(Decl) for (Decl; once();)

int main() {
    for (size_t i = 0; i < 3; i++) {
        with(int x = 1) {
            std::cout << x << "\n";
        }
    }
}
