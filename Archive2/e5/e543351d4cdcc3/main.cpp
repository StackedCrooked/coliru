#include <iostream>
#include <typeinfo>


template<typename T> void foo(T t) {
    std::cout << typeid(t).name();
}

int main()
{
    foo("text");
}
