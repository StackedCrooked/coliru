#include <iostream>
#include <vector>
#include <string>

std::ostream & operator<<(std::ostream & out, std::vector<std::string> const & items)
{
    for(auto const & item : items ) 
        out << item << " ";
    return out;
}

int main() 
{
    std::cout << "GCC " << __VERSION__ << std::endl;
    
    std::vector<std::string> items {"default"};
    
    auto add = [=](std::string item) mutable { items.push_back(item); return items; } ;
    
    std::cout << add("one") << std::endl;
    std::cout << add("two") << std::endl;
    std::cout << add("three") << std::endl;
}