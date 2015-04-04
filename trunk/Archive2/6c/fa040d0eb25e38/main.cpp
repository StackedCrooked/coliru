#include <iostream>
#include <memory>

using namespace std;
 
struct X {
  
  X() { cout<<"X()"<<endl; }
  ~X() { cout<<"~X()"<<endl; }
  void f() {}
};
 
int main()
{
    shared_ptr<X> sp(new X);
    
    weak_ptr<X> wp(sp);
    cout<<wp.expired()<<endl;
}