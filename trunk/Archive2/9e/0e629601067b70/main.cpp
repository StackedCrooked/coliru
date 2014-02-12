#include <iostream>
#include <memory>

class Fxx
{
public:
    Fxx()      { std::cout << "Fxx::Fxx\n";  }
    ~Fxx()     { std::cout << "Fxx::~Fxx\n"; }
    void bar() { std::cout << "Fxx::bar\n";  }
};


class Foo
{
public:
    Foo()      { 
        std::cout << "Foo::Foo\n";  }
    ~Foo()     { std::cout << "Foo::~Foo\n"; }
    void bar() { std::cout << "Foo::bar\n";  }
};
 
void f(const Foo &)
{
    std::cout << "f(const Foo&)\n";
}
 
int main()
{
    //std::unique_ptr<Foo> p1(new Foo);  // p1 owns Foo
    //if (p1) p1->bar();
 
    {
     //   std::unique_ptr<Foo> p2(std::move(p1));  // now p2 owns Foo
     //   f(*p2);
      //  std::cout << "xxx\n";
        std::unique_ptr<Foo> sas(new Foo);
        //Foo* sas;
        //sas = new Foo();
        sas->bar();
        //delete sas;
 
    //    p1 = std::move(p2);  // ownership returns to p1
    //    std::cout << "destroying p2...\n";
    }
    //std::cout << "xxx\n";
 
    //if (p1) p1->bar();
    //else std::cout << "kupa\n";
 
    // Foo instance is destroyed when p1 goes out of scope
}