#include <random>
#include <iostream>
#include <memory>
#include <functional>
 
template <typename T>
struct blah {
    
    void Register( std::function<bool(const T&)> consumer )
    {
        std::cout << " std::function\n" ;
    }
    
    
    template <typename FunctionObject>
        inline void Register(const FunctionObject& consumer)
        {
        std::cout << "FunctionObject\n" ;
    
    }
};
 
 struct A{};
 void func(con)
int main()
{
    
    funct(A());
    using namespace std::placeholders;  // for _1, _2, _3...
 
    blah<int> b1 ;
 
    b1.Register( [] ( const int &x ) -> bool { return x < 10 ; } ) ;
    
    auto f = [] ( const int &x ) -> bool { return x < 10 ; } ;
    
    b1.Register( f ) ;
    
    std::function<int(int)> f2 = [] (int x ) -> int { return x + 10 ;} ;
    
    std::bind(f2, std::placeholders::_1); // a copy of e is stored in rnd
    
    }