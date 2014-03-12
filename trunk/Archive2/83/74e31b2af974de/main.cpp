#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>

int main()
{
    std::set<std::string> s { "elem1", "elem2", "elem3" };
	std::map<std::string, std::set<std::string>> data;
    
    data.insert(std::make_pair("KEY", s));
    data.insert(std::make_pair("KEY1", s));
    
    for (auto& i : data) {
        std::cout << i.first << ": ";
        
        std::string delim;
        
        for (auto& s : i.second) {
            std::cout << delim << s;
            
            delim = ", ";
        }
        
        std::cout << std::endl;
    }
    
	return 0;
}
