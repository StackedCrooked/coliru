#include <iostream>
#include <string>
#include <vector>

template<bool select, class DUMMY = void>
struct CONDITION_HELPER{};        

template<class DUMMY>
struct CONDITION_HELPER<true, DUMMY>{
  template<class FN1, class FN2>
  static auto fire(FN1 &&fn1, FN2 &&) -> decltype( fn1() ){
    return fn1();
  }
};        

template<class DUMMY>
struct CONDITION_HELPER<false, DUMMY>{
  template<class FN1, class FN2>
  static auto fire(FN1 &&, FN2 &&fn2) -> decltype( fn2() ){
    return fn2();
  }
};        

template<bool first, class FN1, class FN2>
auto if_else(FN1 &&fn1, FN2 &&fn2) -> decltype(
    CONDITION_HELPER<first>::fire(
            std::forward<FN1>(fn1),
            std::forward<FN2>(fn2)
        )   
    ){
    return CONDITION_HELPER<first>::fire(
        std::forward<FN1>(fn1),
        std::forward<FN2>(fn2)
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


public:
    template<bool do_it>
    void go(){
        
        auto data = typename std::conditional<do_it,B,A>::type{};
        
        std::cout << std::is_same<decltype(data), A>::value;
        
        
        std::cout << if_else<do_it>(
                    [&]{ return fn1(data); },
                    [&]{ return fn2(data); }
                );                
    }
};

int main(){
    Test().template go<false>();
    return 0;
}

