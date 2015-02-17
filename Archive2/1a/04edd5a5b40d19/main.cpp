#include <stdio.h>
#include <typeinfo>

template <typename T>
struct foo
{
    template <typename U>
    static void bar() {}
};

template <typename T>
void baz() {
    puts(typeid(&foo<T>::template bar<int>) == typeid(int)
        ? "true" : "false");
}

int main() {
    baz<double>();
}