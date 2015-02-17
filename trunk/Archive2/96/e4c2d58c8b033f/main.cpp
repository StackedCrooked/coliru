#include <stdio.h>
#include <typeinfo>

template <typename RET_TYPE>
struct Class
{
    template <typename T>
    static void Method() {}
};

template <typename RET_TYPE>
void Function() {
    puts(typeid(&Class<RET_TYPE>::template Method<int>) == typeid(int)
        ? "true" : "false");
}

int main() {
    Function<double>();
}