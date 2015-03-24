#include <iostream>

class foo {
private:
    const int secondConst;
    const int firstConst;
public:
   foo(int x) :
          firstConst(x),
          secondConst(firstConst*3)
   {
       // constructor code here....
   }
   
   void print()
   {
       std::cout << firstConst << secondConst << std::endl;
   }
};

int main()
{
   foo(3).print();
   return 0;
}