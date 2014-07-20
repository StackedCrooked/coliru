#include <vector>
#include <iostream>

struct V
{
    V() { std::cout << "ctor\n"; }
	~V() { std::cout << "dtor\n"; }
	V(const V&) { std::cout << "copy ctor\n"; }
	V(V&&) { std::cout << "move ctor\n"; }
};

// Функция:
void someFunc(const V v)
{
	std::cout << "someFunc" << std::endl;
}
 
V makeObject() 
{ 
	return V();
}
 
int main()
{
	// Вызываю её так:
	someFunc( makeObject() ); // сработает ли move-конструктор, ведь someFunc принимает const? 	
}
