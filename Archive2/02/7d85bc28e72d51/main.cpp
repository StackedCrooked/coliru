#include <iostream>

class A{
public:
    double f(double x){
        std::cout << "a" <<std::endl;
        return x;
    }
};

class B{
public:
    double f(double x){
        std::cout << "b" <<std::endl;
        return x ;
    }
};

    template <typename T>
    double myfun(T t){
        return t.f(1.0);
    }

int main()
{
    A a1 ;
    B b1 ;
    
    myfun( a1 ) ;
    myfun( b1 ) ;
}