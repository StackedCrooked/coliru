#include <functional>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
    
class Base {};

class Derived : public Base {};

class Foo {
    public:
  void doit( const Base& bar ) {
    cout << "do it !"; 
  }
};

    
    
int main() 
{
    Foo foo;
    std::function<void ( const Base& )> fn = std::bind(&Foo::doit, &foo, std::placeholders::_1);
    
    Base base;
    fn( base );
    
    Derived derived;
    fn( derived );
      
    return 0;
}