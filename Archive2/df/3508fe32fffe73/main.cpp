#include <iostream>
#include <unordered_set>
 
int main()
{  
    std::unordered_set<int> example = {1, 2, 3, 4};
 
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "Found " << (*search) << '\n';
    }
    else {
        std::cout << "Not found\n";
    }
}