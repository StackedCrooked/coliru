#include <iostream>
struct A
{
    A() {std::cout << __PRETTY_FUNCTION__ << '\n';};
    A(A&&) {std::cout << __PRETTY_FUNCTION__ << '\n';};
    A(const A&) {std::cout << __PRETTY_FUNCTION__ << '\n';};
	~A() {std::cout << __PRETTY_FUNCTION__ << '\n';};
};

struct B
{
	A a;
	A&& f() && {return std::move(a);}
};

int main()
{
    {
        std::cout << "-\n";
        A&& a = B().f();
	    std::cout << &a << '\n';
    }
    {
        std::cout << "-\n";
	    A a = B().f();
	    std::cout << &a << '\n';
    }
}
