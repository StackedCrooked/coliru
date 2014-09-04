#include <iostream>

template <class...> class test;

template <
    template <class...> class tp,
    class...arg1Ts,
    class...arg2Ts
> 
class test < tp<arg1Ts...>, tp<arg2Ts...> > {
public:
    void test1(arg1Ts..., arg2Ts...) {
        std::cout << sizeof...(arg1Ts) << ' ' << sizeof...(arg2Ts) << '\n';
    }
};

template <typename...> class Pack;

int main(){
   using tuple0 = std::tuple<int, char, double>;
   using tuple1 = std::tuple<float, unsigned long>;
   test< tuple0, tuple1 > t1;

}