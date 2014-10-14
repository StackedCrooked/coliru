#include <iostream>
#include <string>
#include <functional>
 
int main()
{
    std::string s = "Stand back! I've got jimmies!";
    std::hash<std::string> hash_fn;
 
    size_t hash = hash_fn(s);
 
    std::cout << hash << '\n';
}