#include <iostream> 
struct A;
struct B{
    B(int){ std::cout << "B constructor\n";}
    
    B(const B&) { std::cout << "B copy contructor \n";}
    B(B&&) { std::cout << "B move contructor \n";}
    
   // explicit B(const A&) { std::cout << "B converting contructor \n";}
    
};
struct A{  
    operator B() {std::cout <<" A conversion \n"; return 1;}; 
};
int main()
{
   //B b_direct{A{}};
   B& b_copy = {A{}};
}