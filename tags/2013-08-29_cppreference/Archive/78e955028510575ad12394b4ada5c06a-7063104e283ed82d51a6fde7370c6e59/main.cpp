#include <iostream>
#include <string>
#include <vector>

struct base 
{
    virtual base* foo()
	{
		return this;
	}
};

struct derive : virtual base 
{
	virtual derive* foo()
	{
		return this;
	}
};


int main()
{
	base* der = new derive;
	if(false)
		derive* der2 = static_cast<derive*>(der);
}