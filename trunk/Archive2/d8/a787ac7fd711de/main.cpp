#include <iostream>
#include <string>
#include <vector>

struct A {
    void fun () {std::cout << "Hello!\n";}
};

int main()
{
    A* a = 0;
    a->fun();
}
