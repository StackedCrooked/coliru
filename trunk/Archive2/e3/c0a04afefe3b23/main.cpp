#include <string>
#include <boost/type_traits.hpp>
#include <iostream>
class Bar;
class FooBase
{
public:
  FooBase( Bar &ctx ) : _barCtx( ctx ) {};
  virtual ~FooBase() {};

  // Some other functions

protected:
  Bar &_barCtx;
};

class Baz;
template< typename T >
class Foo : public FooBase
{
public:
  Foo( Bar &ctx ) : FooBase( ctx ) {};
  
  template<typename U = T, typename = typename boost::enable_if_c<!boost::is_same<U, Baz>::value>::type>
  bool doSomething( int a ) {
      std::cout << "doSomething( int a )\n";
  }
  
  template<typename U = T, typename = typename boost::enable_if_c<boost::is_same<U, Baz>::value>::type>
  bool doSomething( std::string &str, int x, float g ) {
      std::cout << "doSomething( std::string &str, int x, float g )\n";
  }
};

class Bar{};
int main() {
    Bar a;
    
    Foo<std::string> b(a);
    b.doSomething(10);
    //b.doSomething("he", 2, 2.f);  //Compile error
 
    Foo<Baz> c(a);
    std::string lalala("lalala");
    //c.doSomething(10); //Compile error
    c.doSomething(lalala, 2, 2.f); 
}

