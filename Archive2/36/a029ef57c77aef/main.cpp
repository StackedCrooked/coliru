#include <iostream>
#include <set>
 
int main()
{  
    std::set<int> example = {1, 2, 3, 4};
 
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "Found " << (*search) << '\n';
    }
    else {
        std::cout << "Not found\n";
    }
}