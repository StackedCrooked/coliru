#include <iostream>
using namespace std;
class A
{ 
  private:
  int count;
  char *ptr;                                 
  public :
  void print()
  {    
  cout << "Addr " << &ptr << endl;     
  cout << "Addr " << *ptr << endl;     
  }       
  A() :ptr(new char[1024]) {}
  ~A() {delete ptr;}
};

int main()
{
 A obj;
 obj.print();
 A *obj1 = new A(obj); 
 obj1->print();
 cin.get();             
 return 0;   
}