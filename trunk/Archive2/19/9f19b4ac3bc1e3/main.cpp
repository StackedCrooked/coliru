#include <iostream>
#include <string>
#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

struct Foo {
    Foo() { }
};

struct Bar {
    Bar() { }
};

class ToStringVisitor : public boost::static_visitor<string> 
{
public:
   template<typename T>
   string operator()(const T &value) const {
      return boost::lexical_cast<string>(value);
   }

   string operator()(const Foo &value) const {
      return "FOO";
   }
   
   string operator()(const Bar &value) const {
      return "BAR";
   }   
};

int main()
{
   boost::variant<Foo, Bar, int, string> value;
   value = Foo();
   cout << boost::apply_visitor( ToStringVisitor(), value ) << endl;
   
   value = Bar();
   cout << boost::apply_visitor( ToStringVisitor(), value ) << endl;
   
   value = 10;
   cout << boost::apply_visitor( ToStringVisitor(), value ) << endl;
   
   value = "my_string";
   cout << boost::apply_visitor( ToStringVisitor(), value ) << endl;

   return 1;
}
