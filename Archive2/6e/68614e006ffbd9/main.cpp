#include <iostream>
#include <string>
#include <vector>
#include <cassert>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << '[';
    for (auto& el : vec)
    {
        os << "'" << el << "' ";
    }
    os << ']';
    return os;
}

std::vector<std::string> parse_str(const std::string& str)
{
    bool quote {false};
    std::vector<std::string> result{};
    std::string tmp{};
 
    for(const char c : str)
    {
        if(c == '"')
        {
        //" fermant
            if(quote)
            {
                quote = false;
                result.push_back(tmp);
                tmp.clear();
            }
            else
            { //" ouvrant
                quote = true;
            }
        }
 
        //pas un ",
       if(quote && c != '"') {
           tmp += c;
        }
    }
 
    assert(quote == false);
    
    return result;
}

int main()
{
    std::string chaine {"\"Ceci\", \" est une\", \"chaine!\""};
    std::cout << parse_str(chaine);
}
