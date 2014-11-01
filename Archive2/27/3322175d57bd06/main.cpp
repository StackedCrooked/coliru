#include <iostream>

class Base
{
public:
    virtual ~Base(){}
    
    typedef int func_t (int x);
	
	virtual func_t function = 0;

    virtual int function2(int x) = 0;
};

class Derived : public Base
{
public:
    func_t function;
    int function2 (int x);
};

int Derived::function(int x)
{
	return x;
}

int Derived::function2(int x)
{
    return x;
}

int main()
{
	Base * theClass = new Derived();
	
	std::cout << theClass->function(1) << std::endl;
	std::cout << theClass->function2(2) << std::endl;
	
	delete theClass;
	
	return 0;
}