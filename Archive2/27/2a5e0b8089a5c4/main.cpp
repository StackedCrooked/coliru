#include <type_traits>
#include <iostream>

template<class datatype, class FN1, class FN2>
auto if_else(std::true_type,datatype&& data, FN1 &&fn1, FN2 &&) 
{return fn1(std::forward<datatype>(data));}

template<class datatype, class FN1, class FN2>
auto if_else(std::false_type,datatype&& data, FN1 &&, FN2 &&fn2)
{return fn2(std::forward<datatype>(data));}


// ------------------------------------------------------------------------------------------------------------



struct A{
    int id= 4;
};

struct B : A{
    int h = 900;
};

class Test{
    
//template<class B>
int fn1(B &a){
    std::cout << "fn1 " << a.h;
    return a.h;
};

//template<class A>
int fn2(A &a){
    std::cout << "fn2 " << a.id;
    a.id = 9;
    return a.id;
};


public:
    template<bool do_it>
    void go(){
        std::integral_constant<bool,do_it> do_first;
        
        using datatype = typename std::conditional<do_it,B,A>::type;
        datatype data;
        std::cout << std::is_same<decltype(data), A>::value;
        
        std::cout << if_else(do_first,
            *this,
            [&](auto self){ return self.fn1(data); },
            [&](auto self){ return self.fn2(data); }
        ) << '\n';
    }
};

int main(){
    Test().template go<false>();
    Test().template go<true>();
    return 0;
}

