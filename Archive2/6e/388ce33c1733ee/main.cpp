#include <iostream>
#include <type_traits>

struct A
{
    static const char funnyName[];
};

const char A::funnyName[] = "AaAaA";

struct B : A
{
    static const char funnyName[];
};

const char B::funnyName[] = "bBbBb";

template <typename T>
std::string GetFunnyName(T&&)
{
    return std::remove_reference<T>::type::funnyName;
}

int main()
{
    A a;
    B b;
    
    std::cout
        << GetFunnyName(a) << std::endl
        << GetFunnyName(b) << std::endl;
}