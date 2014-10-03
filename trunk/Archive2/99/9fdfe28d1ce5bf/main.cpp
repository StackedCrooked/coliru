#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    /*std::ifstream ifs("main.cpp");
    ifs.unsetf(std::ios_base::skipws);
    using T = char;
    std::copy(std::istream_iterator<T>(ifs),
              std::istream_iterator<T>(),
              std::ostream_iterator<T>(std::cout, ""));
    
    ifs.close();*/
    
    std::string test = "a b c";
    std::string c;
    std::istringstream iss(test);

    while (iss >> c)
    {
        std::cout << c;
    }
    
    return 0;
}