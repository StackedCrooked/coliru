#include <vector>
#include <string>
#include <iostream>
#include <bitset>
#include <memory>
 
int main() 
{
    std::unique_ptr<std::bitset<32>>     value(new std::bitset<32>);
    (*value)[1] = true;
    std::cout << value->to_string() << std::endl;
    
    std::string     str(reinterpret_cast<char const*>(value.get()), sizeof(*value));
    
    std::cout << str.size() << std::endl;
    
    std::bitset<32> const    *test = reinterpret_cast<std::bitset<32> const *>(str.data());
    std::cout << test->to_string() << std::endl;
}