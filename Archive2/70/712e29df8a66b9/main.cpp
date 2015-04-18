#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

std::string dropRightConst(std::string& str)
{
    std::size_t pos = str.rfind('*');
    if (pos == std::string::npos)
        return str;
    
    pos = str.find("const", pos);
    
    if (pos == std::string::npos)
        return str;
    
    return str.substr(0, pos);
}

std::string flipConst (std::string& str)
{
    std::string const_token = "const ";
    std::string asterisk_token = "*";
    if (str.find(const_token) == 0)
    {
        std::size_t asterisk_pos = str.find(asterisk_token);
        if ( asterisk_pos != std::string::npos) // there is at least one asterisk
        {
            return std::string(str.begin() + const_token.size(), str.begin() + asterisk_pos) + const_token + std::string(str.begin() + asterisk_pos, str.end());
        }
        else // there isn't an asterisk
        {
            return std::string(str.begin() + const_token.size(), str.end()) + const_token.drop();
        }
    }
    return str;
}

int main()
{
    std::string in = "const int * const";
    std::string in2 = "const int * ";
    std::string in3 = "const int * const * const";
    std::string in4 = "const int";
    std::cout << dropRightConst(in) << std::endl;
    std::cout << flipConst(in2) << std::endl;
    std::cout << flipConst(in3) << std::endl;
    std::cout << flipConst(in4) << std::endl;
}
