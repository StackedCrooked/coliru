#include <iostream>
#include <vector>

template <typename T>
void CheckPower(T v) {
    std::cout << v << " is " << ((v & (v - 1)) == 0) << std::endl;
}

int main() {
    std::vector<unsigned> list = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    for (const auto& e : list) {
        CheckPower<unsigned>(e);    
    }
}