#include <iostream>

struct loud
{
    loud() { std::cout << "default\n"; }
    loud(loud &&) { std::cout << "move\n"; }
    ~loud() { std::cout << "dtor\n"; }
};

int main()
{
    loud l0{ loud() };
    loud l1( static_cast<loud&&>(loud()) );
}