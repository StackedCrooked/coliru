#include <iostream>

struct Foo { Foo(int x, int y) { std::cout << "Foo(int = " << x << ", int = " << y << ")" << std::endl; } };

void bar(int x, int y) { std::cout << "bar(int = " << x << ", int = " << y << ")" << std::endl; }

void bar(std::initializer_list<int> const& l)
{
    auto it = l.begin(); 
	while (it != l.end())
	{
		std::cout << "arg" << std::distance(l.begin(), it) << " : " << *it << std::endl;
		++it;
	}
}

int main()
{
   Foo({}, {});   // Foo(int = 0, int = 0)
   Foo({1}, {2}); // Foo(int = 1, int = 2)
   Foo({1, 2});   // Foo(int = 1, int = 2)

   bar({}, {});   // bar(int = 0, int = 0)
   bar({1}, {2}); // bar(int = 1, int = 2)
   bar({1, 2});   // error: no matching function for call to 'bar'  <<< Why? <<<
}