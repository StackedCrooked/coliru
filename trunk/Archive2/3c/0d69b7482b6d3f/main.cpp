#include <iostream>

class Foo
{
public:
    void operator() (const Foo& f)
    {
        std::cout << "Foo " << f.goo;   
    }
    
    int goo;
};

auto main() -> int
{
    char a;
    short int b;
    int c;
    long int d;
    long long int e;
    float f;
    double g;
    
    Foo h;
    h.goo = 3;
    Foo i;
    i(h);
    
    return 0;
}