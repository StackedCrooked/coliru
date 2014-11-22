#include<iostream>
#include <tuple>

template<std::size_t N, typename... Types>
using Type = typename std::tuple_element<N, std::tuple<Types...>>::type;

struct X
{
    virtual void foo() = 0;   
};

struct Y : public X
{
    void foo(){}
};

int main(){
   Type<0, int, double, X> t1;
   Type<1, int, double, X> t2;
   Type<2, int, double, X>* t3 = new Y();
};
