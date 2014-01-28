#include <iostream>

struct string
{
    constexpr static const char value[] = {'a', 'b'};
};

constexpr const char string::value[];

int main ()
{
    std::cout << string::value << std::endl;

    return 0;
}
