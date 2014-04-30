#include <iostream>

struct Thing
{
    int test = 1;
    Thing(){}
    Thing(int chooseme) : test(chooseme) {}
};

int main()
{
    Thing t;
    std::cout << t.test << std::endl;
    Thing t2{2};
    std::cout << t2.test << std::endl;
}