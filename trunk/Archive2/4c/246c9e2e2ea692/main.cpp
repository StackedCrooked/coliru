#include <iostream>
#include <typeinfo>

class Base
{
public:
    virtual void foo()
	{
		std::cout << __FUNCTION__ << " Base " << __LINE__ << std::endl;
		goo();
		doo();
	}

	virtual void goo()
	{
		std::cout << __FUNCTION__ << " Base  " << __LINE__ << std::endl;
	}

	void doo()
	{
		std::cout << "this type : " << typeid(*this).name() << std::endl;
		std::cout << __FUNCTION__ << " Base " << __LINE__ << std::endl;
        goo();
	}

	virtual ~Base()
	{}
};

class Derived : public Base
{
public:
	virtual void foo()
	{
		goo();
		doo();
		std::cout << "this type : " << typeid(this).name() << std::endl;
		std::cout << __FUNCTION__ << " Derived " << __LINE__ << std::endl;
	}

	virtual void goo()
	{
		std::cout << "this type : " << typeid(this).name() << std::endl;
		std::cout << __FUNCTION__ << " Derived " << __LINE__ << std::endl;
	}

	void doo()
	{
		std::cout << "this type : " << typeid(this).name() << std::endl;
		std::cout << __FUNCTION__ << " Derived " << __LINE__ << std::endl;
	}

	~Derived()
	{}
};

int main()
{
	Base* b = new Derived;
	std::cout << "object type : " << typeid(b).name() << std::endl;
	b->foo();
	std::cout << std::endl << std::endl;
	b->doo();
}