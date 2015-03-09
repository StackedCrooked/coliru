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

int main()
{
    char a;
    short int b;
    int c;
    long int d;
   // long long int e;
    float f;
    double g;
    
    const char* chinese_mu = "無";
    const char* chinese_li = "里";
    
    Foo h;
    h.goo = 3;
    Foo i;
    i(h);
    
    std::cout << chinese_mu << chinese_li;
    
    return 0;
}