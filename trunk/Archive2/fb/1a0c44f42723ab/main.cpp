#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

int main()
{
    // Somewhere in my code, create persons and fill the vector of persons
    std::string s = "We a1re really awe~~~some";
    std::istringstream str(s);
    std::vector<std::string> v;
    
    std::copy_if(
        std::istream_iterator<std::string>(str), 
    	std::istream_iterator<std::string>(),
    	std::back_inserter(v),
    	[](const std::string& sp) { return std::find_if(std::begin(sp), std::end(sp), [](char c) { return !std::isalpha(c); } ) == std::end(sp); } 
    	);
    
    for(auto& w : v)
       std::cout << w << "\n";    
    
    return 0;
}