#include <iostream>

class B { double a; int b; };
class D : public B { int c; };

int main()
{
    std::cout << sizeof(B) << " " << sizeof(D);
}

 