#include <iostream>
#include <string>
#include <vector>
#include <memory>

class A {
private:
    void foo();

public:
    
class B {
public:    
    B() {
        A a;
        a.foo();
    }    
};
};


int main()
{
    A::B b;
    return 0;
}
