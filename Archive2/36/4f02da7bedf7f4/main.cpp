#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <limits>

void doMath(const std::string& expression) {
    std::istringstream iss(expression);
    double f, k;
    std::string operation;
    
    std::cout << expression << " = ";
    
    if (iss >> f >>  operation  >> k) {
        
        if ( operation.compare("+") == 0 )
            std::cout << f + k;
        else if ( operation.compare("-") == 0 )
            std::cout << f - k;
        else if ( operation.compare("*") == 0 )
            std::cout << f * k;
        else if ( operation.compare("/") == 0 )
            std::cout << f / k;
        else if ( operation.compare("**") == 0 )
            std::cout << pow(f,k);
        else
            std::cout << "ERROR: Operation not supported";

        std::cout << std::endl;
    }
}    

template <typename T>
void getValue(T &v) {
    for (std::cin >> v; !std::cin; std::cin >> v) {
        std::cout << "ERROR\n";
        std::cin.clear(); // clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    }
}

void getExpression(std::string &mystr) {
    double f, k;
    std::cout << "Please enter an expression (like `4 * 5` or `ln 5`): ";
    getValue<double>(f);
    
    while (isspace(std::cin.peek()))
        std::cin.get();
    
    std::cin >> mystr;
    getValue<double>(k);
    
    mystr = std::to_string(f) + " " + mystr + " " + std::to_string(k);
}

int main() {
    std::string mystr;
    getExpression(mystr);
    doMath(mystr);
}