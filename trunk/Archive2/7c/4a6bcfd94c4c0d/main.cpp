#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
using namespace std;
using std::placeholders::_1;

int main() {
    std::string v1 = "foo";
	std::string v2 = "foo";
	
    {
    	bool r = 
    	    std::bind(
    	        static_cast<bool(*)(const std::string&, const std::string&)>(std::operator==<char, std::char_traits<char>, std::allocator<char>>),
    	        std::placeholders::_1,
    	        std::cref(v1))(v2);
    	std::cout << r << '\n';
    }
    {
        bool r = 
    	    std::bind(
    	        std::equal_to<>(),
    	        std::placeholders::_1,
    	        std::cref(v1))(v2);
    	std::cout << r << '\n';
    }
}
