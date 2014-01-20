#include <iostream>

struct Functor
{
    void operator()()
    {
        std::cout << "lol\n";
    }
};

int main()
{
    Functor f;
    f();  // output: "lol"
}