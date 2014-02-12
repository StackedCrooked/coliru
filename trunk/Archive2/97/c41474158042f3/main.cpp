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

class SomeClass {
    public:
     SomeClassUsedInCode scc;
     void print(){
     this->scc.print();
 }
};


int main()
{
    SomeClass sc;
    sc.print();

}
