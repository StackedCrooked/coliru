#include <iostream>
#include <locale>
#include <sstream>

class Foo {
private:
     int a;
     std::string b;
public:
     int getA() { return a; };
     std::string getB(); // in .cpp file
      // there are a bunch of minor functions here, implemented in foo.cpp, but nothing special
};

class Bar {
private:
     Foo* foo;
     int someInt;
public:
     Bar() : foo(new Foo()), someInt(3) { }; // default
     Bar(Foo *foo_, int someInt_) : foo(foo_), someInt(someInt_) {};
     ~Bar() { delete foo; };
     // some other functions
};

int main()
{
    
}