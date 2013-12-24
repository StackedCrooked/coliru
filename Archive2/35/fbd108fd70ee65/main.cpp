#include <iostream>
#include <typeinfo>

class component
{
    public:
		
		component()
		{

		}

		virtual ~component()
		{

		}
};

class two_dimensional_mesh : public component
{
	
};

class three_dimensional_mesh : public component
{
	
};

int main()
{
	component* a = new three_dimensional_mesh;
	component* b = new two_dimensional_mesh;
	component* c = new component;

	std::cout << typeid(a).name() << std::endl;
	std::cout << typeid(*a).name() << std::endl;
	std::cout << typeid(b).name() << std::endl;
	std::cout << typeid(*b).name() << std::endl;
	std::cout << typeid(c).name() << std::endl;
	std::cout << typeid(*c).name() << std::endl;
}