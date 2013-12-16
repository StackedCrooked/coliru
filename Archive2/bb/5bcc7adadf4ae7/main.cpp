#include <iostream>
#include <cstdlib>
using namespace std;

class A
{
protected:
int x;

public:
A(int);
~A();
void set_x(int);
void wypisz() const;
};

int main()
{
A object(45);
object.set_x(345);
object.wypisz();

return 0;
}

A::A(int xx)
:x(xx) 
{ 
cout<<"constructor of A: ";
this->wypisz();
}

A::~A() 
{
cout<<"destructor of A: ";
this->wypisz();
}

void A::set_x(int arg)
{
this->x=arg;
}

void A::wypisz() const
{ 
cout<<this->x<<endl;
}
