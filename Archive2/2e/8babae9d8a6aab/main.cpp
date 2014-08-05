#include <iostream>

using namespace std;

class A {
    protected:  // public ?
        void foo(int x);
};

class B : A {
    using A::foo; 
};

void A::foo(int x) 
{
}  

int main()
{
    return 0;
}

