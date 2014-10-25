#include <iostream>
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
template<typename... Targs>
void tprintf(const char* format, Targs... Fargs); // recursive variadic function

template <typename T, typename... Targs>
void tprintval(const char* format, T value, Targs... Fargs)
{
    std::cout << value;
    tprintf(format+1, Fargs...);
}
template <typename T, typename... Targs>
void tprintwid(const char*, T, Targs...) {}
template <typename... Targs>
void tprintwid(const char* format, int width, Targs... Fargs)
{
    std::cout.width(width);
    tprintf(format+1, Fargs...);
}
template <typename T, typename... Targs>
void tprintfil(const char*, T, Targs...) {}
template <typename... Targs>
void tprintfil(const char* format, char fill, Targs... Fargs)
{
    std::cout.fill(fill);
    tprintf(format+1, Fargs...);
}
template <typename... Targs>
void tprintlit(const char* format, Targs... Fargs)
{
    std::cout.rdbuf()->sputc(*format);
    tprintf(format+1, Fargs...);
}
template<typename... Targs>
void tprintf(const char* format, Targs... Fargs) // recursive variadic function
{
    switch (*format) {
    case 0:   return;
    case '%': return tprintval(format, Fargs...);
    case '*': return tprintwid(format, Fargs...);
    case '#': return tprintfil(format, Fargs...);
    default:  return tprintlit(format, Fargs...);
    }
}
 
int main()
{
    tprintf("%, world#*% %\n","Hello",'!',5,"",123);
    return 0;
}