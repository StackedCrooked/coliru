#include <iostream>
#include <string>
#include <string.h>

template<typename T>
void parse_impl(T& n, const char* begin, const char* end)
{
    n = 0;
    for (auto i = begin; i != end; ++i)
    {
        char c = *i;
        if (c >= '0' && c <= '9')
        {
            n = 10 * n + (c - '0');
        }
        else
        {
            break;
        }
    }
}

template<typename T, unsigned N>
T parse(const char (&charArray)[N])
{
    T t{};
    parse_impl(t, &charArray[0], &charArray[0] + N);
    return t;
}

template<typename T>
T parse(const char* begin, const char* end)
{
    T t{};
    parse_impl(t, begin, end);
    return t;
}

int main(int argc, char** argv)
{
    std::cout << "argv[0]: " << argv[0] << std::endl;
    std::cout << "argv[1]: " << argv[1] << std::endl;
    std::cout << parse<int>("213") << std::endl;
    std::cout << parse<unsigned long>(argv[1], argv[1] + strlen(argv[1])) << std::endl;
}