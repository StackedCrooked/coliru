#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

typedef int & LInt;
typedef int && RInt;

int main()
{
    std::cerr << std::is_rvalue_reference <LInt &>::value << std::endl;  // 0 -> & + & = &
    std::cerr << std::is_rvalue_reference <LInt &&>::value << std::endl; // 0 -> & + && = &
    std::cerr << std::is_rvalue_reference <RInt &>::value << std::endl;  // 0 -> && + & = &
    std::cerr << std::is_rvalue_reference <RInt &&>::value << std::endl; // 1 -> && + && = &&
}
