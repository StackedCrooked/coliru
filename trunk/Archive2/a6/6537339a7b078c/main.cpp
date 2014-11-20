#include <cstdlib>

static int globalstuff = 42;

int const& foo(int const& passed_in) {
    return rand()%2?  passed_in : globalstuff;
}

int main() {
    int const& uhoh = foo(5); // to extend or not to extend - that is the HALTING problem
}