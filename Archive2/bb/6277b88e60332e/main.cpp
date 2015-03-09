#include <iostream>

class Foo
{
public:
    void operator() (const Foo& f)
    {
        std::cout << "Foo " << f.goo << std::endl;
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
    
    const char* chinese_mu = u8"無";
    const char* chinese_li = u8"里";
    
    Foo h;
    h.goo = 3;
    Foo i;
    i(h);
    
    std::cout << chinese_mu << chinese_li;
    
    return 0;
}