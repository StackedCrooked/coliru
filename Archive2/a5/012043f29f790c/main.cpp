#include <iostream>

void foo(int) {}
void foo(long double) {}
void foo(void*) {}

template<class T>
?????? get_foo_ptr(T v) {
    ???????
}

int main() {
    foo('c'); //char doesn't match perfectly, but ends up going to int overload
    std::cout <<  get_foo_ptr('c'); //print address of function that was just called
}