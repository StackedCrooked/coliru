#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::map<std::string, std::vector<std::string>> dict;
    
    dict["cat"] = {"siamese", "15", "3-legged", "pussy", "George"};
    dict["dog"] = {"terrier", "white", "old"};
    dict["human"] = {"me"};
    
    for (auto data : dict) {
        std::cout << data.first << ": ";
        for (auto var : data.second)
            std::cout << var << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
