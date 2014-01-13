#include <iostream>

template<int n> class SumMulti {
public:
    static const int limitCom = ((1000 - 1)/ n);
    static const int value = n * (limitCom * (limitCom + 1)) / 2;
};
 
template<int first, int second> class Sum {
public:
    static const int sumFirst = SumMulti<first>::value;
    static const int sumSecond = SumMulti<second>::value;
    static const int filter = SumMulti<second * first>::value;
    
    static constexpr int value = sumFirst + sumSecond - filter;
};
 
int main() {
    std::cout << Sum<3,5>::value;
}