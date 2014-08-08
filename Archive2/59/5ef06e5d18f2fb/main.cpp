#include <iostream>
#include <type_traits>

template<typename T>
const char *GetTypeName_helper(T) { return "<unknown>"; }
const char *GetTypeName_helper(signed char) { return "int8"; }
const char *GetTypeName_helper(signed short) { return "int16"; }
const char *GetTypeName_helper(signed int) { return "int32"; }
const char *GetTypeName_helper(signed long) { return "int64"; }

template<class T, typename std::enable_if<std::is_integral<T>::value ||
                                          std::is_floating_point<T>::value>::type* = nullptr >
const char* GetTypeName(T t)
{
    return GetTypeName_helper(T{});
}

int main()
{
    std::cout << GetTypeName<signed char>(static_cast<signed char>(0)) << std::endl;
    std::cout << GetTypeName<signed short>(static_cast<signed short>(0)) << std::endl;
    std::cout << GetTypeName<signed int>(static_cast<signed int>(0)) << std::endl;
    std::cout << GetTypeName<signed long>(static_cast<signed long>(0)) << std::endl;
    std::cout << GetTypeName<signed long long>(static_cast<signed long long>(0)) << std::endl;
}
