#include <iostream>
#include <vector>

int main() {
    std::vector<bool> vec1;
    vec1.push_back(true);
    vec1.push_back(false);
    
    for (bool& i : vec1)
        i = false;
        
    std::vector<int> vec2;
    vec2.push_back(1);
    vec2.push_back(2);
 
    for (int& i : vec2)
        i++;

    return 0;
}