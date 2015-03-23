#include <iostream>
#include <thread>
#include <future>
struct Cat
{
    Cat(){ std::cout << " constructor"<< std::endl;}
    Cat(const Cat &){/* deep copy*/ 
        std::cout << " copy constructor" << std::endl;
    };
    Cat(Cat &&other){
        /*steal other's guts*/
        std::cout << " move constructor " << std::endl;
    };
};
Cat browse(){ 
    return {};
}
int main(){
    
    Cat c1;
    Cat c2 = c1;
    Cat c3 = browse();
 
       
}

