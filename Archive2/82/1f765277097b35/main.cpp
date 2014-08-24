#include <iostream>


class foo
{
public:
    foo()
	{std::cout << "Regular constructor \n";}

	foo(const foo& a)                            //In abscence of const keyword the copy constructor is called
	{std::cout << "Copy constructor \n";}

	foo& operator=(const foo& a) 
	{std::cout << "Copy Assignment operator \n";}
	
	foo(foo&& a)
	{
		std::cout << "Move constructor \n";
	}

	foo& operator=(foo&& a) 
	{std::cout << "Move Assignment operator \n";}

	int a;
};


foo myfunction()
{
	foo d;
	d.a =120;
	return d;
}

int main()
{
	foo a = myfunction();
}