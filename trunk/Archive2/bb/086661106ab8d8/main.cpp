#include <iostream>
 
struct A{
    A(){
        std::cout << "A()\n";
    }
    A& operator=(const A&){
        std::cout << "A::operator=(const A&)\n";
        return *this;
    }
    A& operator=(A&&){
        std::cout << "A::operator=(A&&)\n";
        return *this;
    }
};
 
struct B{
    B(const A&a){
        std::cout << "B(const A&a)\n";
        this->a=a;
    }    
    B(A&&a){
        std::cout << "B(A&&a)\n";
        //note, this wont move the a, since a is not an xvalue. use std::move instead 
        this->a=a;
    }    
    A a;
};
 
int main()
{
    A a;
    //without std::move, this won't move the a either.
    B b(std::move(a));
    //B b(a);
}