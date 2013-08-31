#include <iostream>

template <class Ttype> class MyClass{
    Ttype x;
public:
	void set_x(Ttype i){x = i;}
	Ttype get_x(){return x;}
};



int main ()
{
	MyClass <int> ob1;
	MyClass <float> ob2;

	ob1.set_x(10);
	std::cout << ob1.get_x() << std::endl;

	ob2.set_x(123.644);
	std::cout << ob2.get_x() << std::endl;
	return 0;
}