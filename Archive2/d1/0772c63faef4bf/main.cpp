#include <cstdio>

/*
 * Try this with clang++ and g++ and see how funny it is...
 */
 
template<typename T>
void funny(T&&) {
    printf("rvalue reference\n");
}

template<typename T>
void funny(T&) {
    printf("reference\n");
}

struct Alpha {};

int main() {
    Alpha a;
    funny(a);
    return {};
}