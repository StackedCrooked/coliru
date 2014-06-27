#include <type_traits>
#include <iostream>
#include <utility>

template<class FN1, class FN2, class... Args>
auto if_else(std::true_type, FN1 &&fn1, FN2 &&, Args&&... args) 
-> decltype(std::forward<FN1>(fn1)(std::forward<Args>(args)...)) {
     return std::forward<FN1>(fn1)(std::forward<Args>(args)...);
}

template<class FN1, class FN2, class... Args>
auto if_else(std::false_type, FN1 &&, FN2 &&fn2, Args&&... args) 
-> decltype(std::forward<FN2>(fn2)(std::forward<Args>(args)...)) {
     return std::forward<FN2>(fn2)(std::forward<Args>(args)...);
}

template<bool do_it, class FN1, class FN2, class... Args>
auto if_else(FN1 &&fn1, FN2 &&fn2, Args&&... args) 
-> decltype(if_else(std::integral_constant<bool,do_it>{}, fn1, fn2, std::forward<Args>(args)...)) {
     return if_else(std::integral_constant<bool,do_it>{}, fn1, fn2, std::forward<Args>(args)...);
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
        typename std::conditional<do_it,B,A>::type data;
        std::cout << std::is_same<decltype(data), A>::value << ' ';
        
        std::cout << if_else<do_it>(
                            [this](B& data){ return fn1(data); },
                             [this](A& data){ return fn2(data); },
                             data
                ) << '\n';
    }
};

int main(){
    Test().template go<true>();
    Test().template go<false>();
}

