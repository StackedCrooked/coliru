#include<iostream>
class a
{
public:
a(){}
    a(a&& b){}
};
class b
{
    a c;
};

int main()
{
	a d;
    a b(d);
}

