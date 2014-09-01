#include <unordered_set>
#include <iostream>

int main()
{
    std::unordered_set<std::string> set;
    set.emplace("Hello");
    
    const char* s1 = "abc";
    const char* s2 = "abc";
    
    std::cout << (&s1) << std::endl;
    std::cout << (&s2) << std::endl;
}