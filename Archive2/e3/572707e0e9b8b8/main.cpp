#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>
#include <regex>


using namespace std;


int main()
{
    
    std::string text = "1.234e-00050";
    std::regex match("(e|E-?)0+");
    std::cout << "Minus " << text << '\n' << std::regex_replace(text, match, "$1") << '\n';    
    
    text = "1.234e00050";
    std::cout << "Plus " << text << '\n' << std::regex_replace(text, match, "$1") << '\n';    

    text = "1.234E00050";
    std::cout << "CAP Plus " << text << '\n' << std::regex_replace(text, match, "$1") << '\n';    

    text = "1.234E-00050";
    std::cout << "CAP Minus " << text << '\n' << std::regex_replace(text, match, "$1") << '\n';    

}
