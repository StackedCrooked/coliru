#include <random>
#include <iostream>
 
struct Base{
    Base(int i){
        std::cout << "Construcetd a base with " << i << std::endl;
    }


};


struct Child : public Base{
    using Base::Base;

};




int main(){

    Child c(1);
}
