#include <iostream>
#include <vector>
#include <deque>


struct Foo
{
    Foo()        				{					std::cout << "Foo()"								<< std::endl; }
	Foo(int _i) : i(_i)			{					std::cout << "Foo(int="					<< i << ")" << std::endl; }
	Foo(Foo&&o) : i(0)			{ std::swap(i,o.i);	std::cout << "Foo(Foo&&="				<< i << ")" << std::endl; }
	Foo(const Foo&o) : i(o.i)	{					std::cout << "Foo(const Foo&="			<< i << ")" << std::endl; }
	Foo&operator=(Foo&&o)		{ i = o.i; o.i = 0;	std::cout << "Foo&operator=(Foo&&="		<< i << ")" << std::endl; return *this; }
	Foo&operator=(const Foo&o)	{ i = o.i;			std::cout << "Foo&operator=(const Foo&="<< i << ")" << std::endl; return *this; }
	~Foo()						{					std::cout << "~Foo("					<< i << ")" << std::endl; }

	int i;
};


std::ostream & operator<<(std::ostream & out, const Foo & foo)
{
	return (out << foo.i);
}


int main()
{
	{
#if 1
		std::vector<Foo> my_array;
		my_array.reserve(3);
#else
		std::deque<Foo> my_array;
#endif
		std::cout << "--------------" << std::endl;
		my_array.emplace_back(1);
		my_array.emplace_back(2);
		my_array.emplace_back(3);
		std::cout << "--------------" << std::endl;
	}

	std::cout << "--------------" << std::endl;
    
    return 0;
}
