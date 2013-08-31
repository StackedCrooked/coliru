#include <iostream>
#include <string>
#include <cstddef>
#include <cassert>

std::string to_columns(std::string& str, std::size_t column_size)
{
    assert(column_size != 0);
    
    std::size_t len{str.size()};
    
    if (len == 0)
        return {""};
    
    std::string res{""};    
    std::size_t columns{len/column_size};
    
    for (std::size_t i{0}; i < column_size; ++i)
    {
        for (std::size_t j{i}; j < len; j += column_size)
        {
            res += str[j];    
        }
        
        res += '\n';
    }
    
    return res;
}

int main()
{
    std::string test{"The quick brown fox jumps over the lazy dog."};
    
    std::cout << to_columns(test, 5) << "\n";
}
