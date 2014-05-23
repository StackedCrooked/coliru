#include <iostream>
class A{
    int i;
public:
	A(int j) : i(j) {}
	A operator=(A& a) { std::cout << "assign " << a.i << " to " << this->i << '\n'; this->i = a.i; return *this; }
	int GetValue() { return i; }
};

int main()
{
	A a(1), b(2), c(3);
	(a = b) = c;	// Equivalent to "(a.operator=(b)).operator=(c);"
					// Note that the expression "(a.operator(b))" is an rvalue of type A, say t. Therefore,
					// "(a.operator=(b)).operator=(c);" is equivalent to "t.operator=(c);" and this last expression will
					// make t.i = 3, not a.i = 3!

	std::cout << a.GetValue() << '\n';		//	a.i is still 2.

//	a = b = c;		//	Doesn't compile. Note that the assigmnment operator is right associative. Therefore
					//	"a = b = c;" is equivalent to "a.operator=(b.operator=(c));", but "b.operator=(c)" is an rvalue,
					//	which doesn't bind to an lvalue reference.

	std::cout << a.GetValue() << '\n';
}