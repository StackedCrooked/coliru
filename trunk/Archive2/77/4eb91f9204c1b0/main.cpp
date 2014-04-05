#include <iostream>

class X
{
    public:
        virtual void activate(){
            std::cout << "I am an X class" << std::endl;
        }
};

class Y : public X
{
    public:
        void activate(){
            std::cout << "I am a Y class" << std::endl;
        }
};

class A 
{ 
    public:
        virtual void foo(X* xptr) = 0; 
};

class B : public A
{
    public:
        void foo(X* xptr) 
        { 
            xptr->activate();
        }
};
    

int main()
{
    Y y_instance;
    B b_instance;
    
    b_instance.foo( &y_instance );
    return 0;
}
