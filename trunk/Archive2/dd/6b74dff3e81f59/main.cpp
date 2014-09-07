#include <iostream>
using std::cout;
using std::endl;

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
   void show() const {cout << size << endl;}
   ~X()
   {
      cout << "X::~X() with size = "<< size << endl;
   }
};

X f()
{
   return X();
}

int main()
{
   X a(3);
   auto const &temp = f();
   temp.show();
   cout << "blah" << endl;
   return 0;
}