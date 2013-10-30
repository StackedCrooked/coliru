#include <iostream>
#include <string>
#include <sstream>

int main(){
    double x = 123.456;
    std::stringstream ss;
    ss << x;
    std::cout << ss.str() << '\n';
}