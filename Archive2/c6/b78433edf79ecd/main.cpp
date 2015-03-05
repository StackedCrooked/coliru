#include <iostream>
#include <string>

template<typename T> struct BackSlash {};

template<> struct BackSlash<char> {
    static const char *value() { return "\\"; }
};
template<> struct BackSlash<wchar_t> {
    static const wchar_t *value() { return L"\\"; }
};

int main()
{
    std::cout << BackSlash<char>::value() << std::endl;
    std::wcout << BackSlash<wchar_t>::value() << std::endl;
    return 0;
}