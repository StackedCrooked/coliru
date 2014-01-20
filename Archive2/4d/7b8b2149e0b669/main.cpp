#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> vec = { "a","b","c" };
    
    std::string space = "";
    std::string result = "";
    auto end = vec.rend();
    
    for(auto it = vec.rbegin(); it != vec.rend(); ++it ) {
        if (it == end - 1) {
            result += *it;
        }
        else {
            result += it[0];
        }        
    
        std::cout << space << *it << std::endl;
        space += " ";
    }
    std::cout << result << std::endl;
}
    