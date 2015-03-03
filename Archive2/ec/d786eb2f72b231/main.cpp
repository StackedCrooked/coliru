#include <iostream>
using namespace std;

template<typename T> void print(T&& mX) 
{
    std::cout << std::forward<T>(mX) << std::endl;  
}

struct SomeStruct
{
    static constexpr const char* someString{"hello!"};
    SomeStruct()
    {
        print(someString);
    }
};

constexpr const char* SomeStruct::someString;

int main() 
{
    SomeStruct s{};
    return 0;
}