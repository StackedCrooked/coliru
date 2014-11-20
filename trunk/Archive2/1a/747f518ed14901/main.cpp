#include <cstdlib>

int foo(int const& passed_in) {
    return rand()%passed_in;
}

int main() {
    int const& uhoh = foo(500); // binds ok, because the return value **is** a temp of it's own
}