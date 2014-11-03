#include <iostream>
#include <type_traits>

template<class T>
class toto{
    T a;
};

template<class T, class D, typename = typename std::enable_if<std::is_arithmetic<D>::value>::type>
toto<T> operator+(toto<T> const&, const D&){
    std::cout <<  "hello " <<std::endl;
    return toto<T>();        
}

int main(){
    toto<float> t;
    toto<float> d = t +2.3;
  //  toto<float> d1 = t + "asd";    
}
