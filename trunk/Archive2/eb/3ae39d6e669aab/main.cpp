#include <iostream>
#include <string>
#include <type_traits>

struct foo
{
    std::string const data_;
};

int main()
{
    foo f;
    foo &fr{ f };
}