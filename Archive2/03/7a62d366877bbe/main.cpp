#include <iostream>
using namespace std ;

class X
{
   unsigned int size;
public:
   X() : size(0)
   {
      cout << "X::X() with size = " << size << endl;
   }
   X(int sz) : size(sz)
   {
      cout << "X::X() with size = " << size << endl;
   }
   void show(){cout << size << endl;}
   ~X()
   {
       static int cnt = 0 ;
      cout << "X::~X() with size = "<< size << " **** destructor# " << ++cnt << '\n' ;
   }
};

X f()
{
    X object ;
    cout << "f()::object.show: " ; object.show() ;
    return object ; // NRVO (named return value optimization) may apply.
}

int main()
{
   X a(3);
   X b = f() ; 
   cout << "------------------\n" ;
}