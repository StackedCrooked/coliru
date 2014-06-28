#include <iostream>
#include <string>
#include <vector>


#define MAKE_IF(c_name, fn1, fn2)\
template<bool select, class DUMMY = void>\
struct c_name{\
};        \
\
template<class DUMMY>\
struct c_name<true, DUMMY>{\
  template<typename SELF, typename ...Args>\
  static auto fire(SELF &&self, Args &&...args)-> decltype( self.fn1(std::forward<Args>(args)...) ){\
    return self.fn1( std::forward<Args>(args)... );\
  }\
};\
\
template<class DUMMY>\
struct c_name<false, DUMMY>{\
  template<typename SELF, typename ...Args>\
  static auto fire(SELF &&self, Args &&...args) -> decltype( self.fn2(std::forward<Args>(args)...) ) {\
    return self.fn2( std::forward<Args>(args)...);\
  }\
};





  template<class FN1, class FN2>
  static auto fire(FN1 &&fn1, FN2 &&, std::true_type) -> decltype( fn1() ){
    return fn1();
  }
  template<class FN1, class FN2>
  static auto fire(FN1 &&, FN2 &&fn2, std::false_type) -> decltype( fn2() ){
    return fn2();
  }


template<bool first, class FN1, class FN2>
auto if_else(FN1 &&fn1, FN2 &&fn2) /*-> decltype(
    fire(
            std::forward<FN1>(fn1),
            std::forward<FN2>(fn2), 
            first
        )   
    )*/{
    return fire(
        std::forward<FN1>(fn1),
        std::forward<FN2>(fn2), 
        std::integral_constant<bool, first>()
    );
}








// ------------------------------------------------------------------------------------------------------------



struct A{
    int id= 4;
};

struct B : A{
    int h = 900;
};

class Test{
int fn1(B &a){
    std::cout << "fn1 " << a.h;
    return a.h;
};

int fn2(A &a){
    std::cout << "fn2 " << a.id;
    a.id = 9;
    return a.id;
};


MAKE_IF(selector, fn1, fn2 )

public:
    template<bool do_it>
    void go(){
        
        auto data = if_else<do_it>(
                    []{ return B(); },
                    []{ return A(); }
                );
        std::cout << std::is_same<decltype(data), A>::value;
        
        
        // Why this not work?
        std::cout << if_else<do_it>(
                    [&]{ return fn1(data); },
                    [&]{ return fn2(data); }
                );
                
        
        // While this work. They are wery similliar
        std::cout << selector<do_it>::fire(*this, data);
        
    }
};

int main(){
    Test().template go<false>();
    return 0;
}

