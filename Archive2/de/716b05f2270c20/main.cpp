#include <iostream>
#include <type_traits>

template<typename T>
const char *GetTypeName(T) { return "<unknown>"; }

const char *GetTypeName(signed char) { return "int8"; }
const char *GetTypeName(signed short) { return "int16"; }
const char *GetTypeName(signed int) { return "int32"; }
const char *GetTypeName(signed long) { return "int64"; }

int main()
{
    std::cout << GetTypeName(static_cast<signed char>(0)) << std::endl;
    std::cout << GetTypeName(static_cast<signed short>(0)) << std::endl;
    std::cout << GetTypeName(static_cast<signed int>(0)) << std::endl;
    std::cout << GetTypeName(static_cast<signed long>(0)) << std::endl;
    std::cout << GetTypeName(static_cast<signed long long>(0)) << std::endl;
}
