#include <type_traits>
#include <string>
#include <iostream>

struct A
{
    template<typename T>
    typename std::enable_if<std::is_enum<T>::value>::type
    blub(T value) { std::cout << "enum\n"; }

    void blub(std::string value) { std::cout << "string\n"; }
    void blub(int value) { std::cout << "int\n"; }
};

enum E { ZERO = 0 };

int main()
{
    A a;
    a.blub(std::string());
    a.blub(42);
    a.blub(ZERO);
}
