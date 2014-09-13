#include <iostream>
#include <cstring>

using namespace std;

struct A
{
    char a = '5';
    int b = 5;
};

A a;

int main()
{
    char c[10];
    std::memcpy(&c, const_cast<A*>(&a), 10);
    for(int i = 0; i < 10; i++)
    {
        std::cout << i << " ";
        std::cout << c[i] << endl;;
    }
}