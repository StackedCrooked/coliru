#include <iostream>
#include <memory>
#include <functional>


template<typename T>
struct Displayable
{    
    friend void display(const Displayable<T>& t) { return static_cast<const T&>(t).display(); }
};


struct Thingy1 : Displayable<Thingy1>
{
	void display() const { std::cout << "Thingy1\n"; }
};

struct Thingy2 : Displayable<Thingy2>
{
	void display() const { std::cout << "Thingy2\n"; }
};


int main()
{
	display(Thingy1());
	display(Thingy2());
}
