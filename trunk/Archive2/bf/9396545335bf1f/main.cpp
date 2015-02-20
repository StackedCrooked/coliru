#include <iostream>
#include <typeinfo>
using namespace std;

#include <iostream>
#include <typeinfo>

class A {

public:
    virtual void f()
    {
        x = 0;
    }
    
    virtual std::string getType()
    {
        return typeid(*this).name();
    }

int x;
};

class B : public A
{
public:
    virtual void f()
    {
        x = 1;
    }
};



int main() {
	
	A* a = new A();
	A* ab = new B();
	B* b = new B();
	
	cout << typeid(a).name() << "\n";
	cout << typeid(ab).name() << "\n";
	cout << typeid(b).name() << "\n";

	cout << a->getType() << "\n";
	cout << ab->getType() << "\n";
	cout << b->getType() << "\n";

    return 0;
    
}
