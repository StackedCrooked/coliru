#include <iostream>

class base
{
    public:
	virtual void print() const { std::cout << "I am base\n"; }
};

class A : public base
{
	public:
	void print() const { std::cout << "I am object A, inherit from base\n"; }
};

class B : public base
{
	public:
	void print() const { std::cout << "I am object B, inherit from base\n"; }
};

class C : public base
{
	public:
	void print() const { std::cout << "I am object C, inherit from base\n"; }
};

class AddThings
{
	public:
	template <typename A, typename B>
	static void the_function( const A &A_object, const B &B_object )
	{
		A_object.print();
		B_object.print();
	}
};

int main()
{
	A Aobject;
	B Bobject;
	C Cobject;
	base baseObject;
	
	AddThings::the_function(Aobject, baseObject);
	AddThings::the_function(Bobject, baseObject);
	AddThings::the_function(baseObject, Cobject);
	AddThings::the_function(Aobject, Bobject);
}