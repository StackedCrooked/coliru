#include <iostream>
#include <string>
#include <vector>

template<class datatype, class FN1, class FN2>
auto if_else(datatype&& data, FN1 &&fn1, FN2 &&) 
-> decltype(fn1(std::forward<datatype>(data)))
{return fn1(std::forward<datatype>(data));}

template<class datatype, class FN1, class FN2>
auto if_else(datatype&& data, FN1 &&, FN2 &&fn2) 
-> decltype(fn2(std::forward<datatype>(data)))
{return fn2(std::forward<datatype>(data));}


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
        using datatype = typename std::conditional<do_it,B,A>::type;
        datatype data;
        std::cout << std::is_same<decltype(data), A>::value;
        
        std::cout << if_else(data,
                    [&](B& data){ return fn1(data); },
                    [&](A& data){ return fn2(data); }
                );                
    }
};

int main(){
    Test().template go<false>();
    return 0;
}

