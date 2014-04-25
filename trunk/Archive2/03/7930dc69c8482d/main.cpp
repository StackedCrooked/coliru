#include <iostream>
#include <typeinfo>

int main()
{
    auto danger_level = "very extreme";
    std::cout << danger_level << '\n'
              << typeid(danger_level).name() << '\n'
              << sizeof(danger_level) << '\n'
              << typeid("very extreme").name() << '\n'
              << sizeof("very extreme") << '\n';
}