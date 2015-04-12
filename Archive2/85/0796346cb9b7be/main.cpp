#include <iostream>

struct ping {
    ping() { std::cout << "ping\n"; }
};

struct foo: ping {
    int i;
};

int main()
{
    {
        foo f;
        std::cout << f.i << '\n';
    }
    
    {
        foo f {};
        std::cout << f.i << '\n';
    }
}