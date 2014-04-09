#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() 
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
    std::vector<std::string> s = {"a", "b", "c", "d"};
    std::map<std::string, std::string> m;
    m["ss"] = "SS";
    m["tt"] = "TT";
    for (auto &i : m)
        std::cout << i.first << ":" << i.second<<" ";
    std::cout << std::endl;
    for (auto &i : s)
        std::cout << i<< ' ';
    std::cout << std::endl;
    
    for (int &i : v) // access by reference (const allowed)
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (auto &i : v) // compiler uses type inference to determine the right type
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (int i : v) // access by value as well
        std::cout << i << ' ';
 
    std::cout << '\n';
}