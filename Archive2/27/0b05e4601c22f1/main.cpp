#include <unordered_set>
#include <unordered_map>
#include <iostream>



int main () { 
    std::cout << "sizeof(std::unordered_set<int>):      " << sizeof(std::unordered_set<int>) << std::endl;
    std::cout << "sizeof(std::unordered_map<int, int>): " << sizeof(std::unordered_map<int, int>) << std::endl;
}