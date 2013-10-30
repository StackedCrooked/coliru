#include <iostream>
#include <string>
#include <sstream>

int main(){
    std::string x = "123.456";
    double y;
    std::istringstream ss(x);
    ss >> y;
    std::cout << y << '\n';
}