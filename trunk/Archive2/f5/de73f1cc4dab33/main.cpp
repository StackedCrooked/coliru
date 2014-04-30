#include <iostream>
static int i = 1000; // #1
void g() {
    int i; // #2 i has no linkage
    {
        extern int i; // #3 external linkage
        std::cout << "Inside g() " << ++i << '\n';
    }
}

class A {
    public:
    ~A() { std::cout << "A destructor " <<  ++i << '\n'; }
};


int main()
{
    A a;
    g();
    std::cout << "Outside g() " << ++i << '\n';
}
