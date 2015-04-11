#include <boost/any.hpp>
#include <vector>
#include <string>
#include <iostream>

template <const char *str1, const char*... str2> struct restrictedValues {};

template<const char* str0, const char *... str>
void validate(restrictedValues<str0, str...>*) {
    std::cout << "custom version\n";
}

extern char const client[] = "hello";
extern char const server[] = "world";

int main()
{
    restrictedValues<client, server>* p = 0;
    validate(p);
}