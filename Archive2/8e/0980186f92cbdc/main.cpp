#include <iostream>
#include <string>
#include <vector>
#include <array>


class SomeClassUsedInCode {
    public:
    void print(){
        std::cout << "Real impl" << std::endl;
    }
  
};
class SomeClassUsedInCodeFake {
    public:
    void print(){
        std::cout << "Fake impl" << std::endl;
    }
  
};

template <class SomeClassImpl>
class SomeClassUT {
    public:
     SomeClassImpl scc;
     void print(){
     this->scc.print();
 }
};

typedef SomeClassUT<SomeClassUsedInCode> SomeClass; // real class
typedef SomeClassUT<SomeClassUsedInCodeFake> SomeClassTC; //testing class

int main()
{
    SomeClass sc;
    sc.print();
    SomeClassTC scf;
    scf.print();
}
