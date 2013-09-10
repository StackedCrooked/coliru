#include <iostream>

class A{
    public:
    A(){
        std::cout<<"Constructor A"<<std::endl;
    }
    
    virtual ~A(){
        std::cout<<"Destructor A"<<std::endl;
    }
};

class B: public A{
    public:
    B(){
        std::cout<<"Constructor B"<<std::endl;
    }
    
    virtual ~B(){
        std::cout<<"Destructor B"<<std::endl;
    }
};

int main(int argc, char* argv[]){
    std::cout<<"A:"<<std::endl;
    {
        A a;
    }
    
    std::cout<<"B:"<<std::endl;
    {
        B b;
    }
    
    std::cout<<"*B:"<<std::endl;
    {
        A *b = new B();
        delete b;
    }
}