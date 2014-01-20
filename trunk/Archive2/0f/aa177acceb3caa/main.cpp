#include <iostream>
#include <cmath>

double eval(int a, int b){
    return std::sqrt(a) + std::sqrt(b);
}

int main(){
    double first = eval(545, 331);
    double second = eval(545, 331);

    if(first < second)
        std::cout << "first <  second" << std::endl;
    if(first == second)
        std::cout << "first == second" << std::endl;
    if(first > second)
        std::cout << "first >  second" << std::endl;
}