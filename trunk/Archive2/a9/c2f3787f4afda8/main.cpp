#include <iostream>
#include <unordered_map>
 
int main()
{  
    std::unordered_map<int,char> example = {{1,'a'},{2,'b'}};
 
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
    }
    else {
        std::cout << "Not found\n";
    }
}