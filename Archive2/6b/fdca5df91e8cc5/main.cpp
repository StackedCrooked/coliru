#include <iostream>
#include <typeinfo>

using namespace std;

class a
{
  public:
  a(){cout<<"in a\n";}
};

int main()
{
  a a1() ;
  a a;
       
  std::cout << typeid(a).name() << std::endl ;
  std::cout << typeid(a1).name() << std::endl ;
}