#include <regex>
#include <iostream>

void example(char const *p)
{
    std::cout << "pointer: " << p << std::endl;
}

template<typename T,
    typename = typename std::enable_if<std::is_convertible<T, char const *>::value>::type>
void example(T&& s)
{
    std::cout << "template called" << std::endl;
    return example(static_cast<char const *>(s));
}

void example(std::string const& s)
{
    std::cout << "string called" << std::endl;
    return example(s.c_str());
}

int main(int argc, char **argv) {
    char *p = "test p";
    example("test");
    example(std::string("Test C++"));
    example(p);
}
