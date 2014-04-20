#include <string>
using namespace std;

std::string rev(std::string x)
{
    auto a=x.begin();
    auto b=x.rbegin(); 

    while (a<b.base())
        swap(*a++, *b++);

    return x;
}

#include <iostream>
int main()
{
    std::cout << rev("") << "\n";
    std::cout << rev("1") << "\n";
    std::cout << rev("12") << "\n";
    std::cout << rev("123") << "\n";
    std::cout << rev("Hello world!") << "\n";
}


