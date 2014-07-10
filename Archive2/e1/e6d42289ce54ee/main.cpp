#include <iostream>

struct foo
{
    float a[100] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};
};

struct bar
{
	float a[100];
	
	bar() : a{}
	{}
};

struct quux
{
	foo f;
	bar b;
	
	quux() : f{} , b{}
	{}
};

int main() {
	quux q;
	
	for(float x : q.f.a )
		std::cout << x;

	std::cout << std::endl;
	
	for(float x : q.b.a )
		std::cout << x;
	return 0;
}