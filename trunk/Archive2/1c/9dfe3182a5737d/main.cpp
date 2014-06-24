#include <iostream>
#include <vector>
#include <memory>

struct A
{
    virtual ~A() { std::cout << "A::~A()\n"; }
};

struct B : A
{
	~B() { std::cout << "B::~B()\n"; }
};

int main()
{
	std::vector<std::unique_ptr<A>> v { new B, new B, new B, new B, new B };
	while(auto it = std::begin(v) && it != std::end(v))
		v.erase(it);
	
	return 0;
}