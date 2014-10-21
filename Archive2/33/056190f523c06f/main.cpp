#include <iostream>
#include <map>
 
int main()
{  
    std::map<std::string,int> example = {{"a",1},{"b",2}};
 
    auto search = example.find(nullptr);
    if(search != example.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
    }
    else {
        std::cout << "Not found\n";
    }
}