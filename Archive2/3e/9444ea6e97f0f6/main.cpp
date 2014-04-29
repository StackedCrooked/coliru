#include <iostream>

class A
{
public:
    void fonctionA(){}
};
 
class B : public A
{
public:
    void fonctionB()
    {
        fonctionA();
    }
};


int main() { B b; b.fonctionB(); }