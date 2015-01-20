#include <iostream>



class Foo0{
public:
  Foo0(int a){};
  void doStuff() {std::cout<<"maap"<<std::endl;};
};



class Foo1{
public:
  Foo1(int a){};
  void doStuff() {std::cout<<"maap"<<std::endl;};
};



class Foo2{
public:
  Foo2(int a){};
  void doStuff() {std::cout<<"maap"<<std::endl;};
};



class Bar{
public:
  Bar(Foo0 foo0, Foo1 foo1, Foo2 foo2){};
};



int main () {

  int x = 1;

  //Bar bar0(Foo0(x), Foo1(x), Foo2(x)); // Does not work: conflicting declaration ‘Foo1 x’ previous declaration as ‘Foo0 x’; conflicting declaration ‘Foo2 x’ previous declaration as ‘Foo0 x’
  //Bar bar1(Foo0{x}, Foo1(x), Foo2(x)); // Works WTF
  //Bar bar2(Foo0(x), Foo1{x}, Foo2(x)); // Works WTF
  Bar bar3(Foo0(x), Foo1(x), Foo2{x}); // Does not work: conflicting declaration ‘Foo1 x’ previous declaration as ‘Foo0 x’
  //Bar bar4(Foo0{x}, Foo1{x}, Foo2{x}); // Works totally makes sens to me

  //x.doStuff(); //Dose not work. This makes sens to me. But in the context its curious though.
}