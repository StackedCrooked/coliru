#include <iostream>

//Difference: 1, 3, 13, 31, 57 = +2 +10 + 18 + 26 === +8
//Difference: 1, 5, 17, 37 = +4 + 12 + 20 === +8

template<unsigned long long int x> class Problem {
public: 
    enum { value = (int)(((16.0 / 3.0) * (x * x * x)) + (10.0 * (x * x)) + ((26.0 / 3.0) * x) + 1) };
};

int main () {
    std::cout << "Solution: " << Problem<500>::value << std::endl;
}