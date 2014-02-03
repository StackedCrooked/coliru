#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

template<typename RandomIt>
std::basic_string<typename RandomIt::value_type> parseStringLiteral(RandomIt st, RandomIt en)
{
    std::vector<typename RandomIt::value_type> result;
    
    for (auto remain = en - st; remain > 0; --remain) {
        if (*st == '\\') {
            if (remain < 1)
                throw std::exception();
            
            switch (st[1])
            {
                case '\\':
                    result.push_back('\\');
                    break;
                
                case 't':
                    result.push_back('\t');
                    break;
                
                case 'n':
                    result.push_back('\n');
                    break;
                
                // etc
            }
            st += 2;
        }
        else if (*st == '"')
        {
            break;
        }
        else
        {
            result.push_back(*st++);
        }
    }
    return std::string(result.begin(), result.end());
}

int main()
{
    std::string example("This is a string literal with tab:\\t and newline:\\n!\" and stuff after the closing quote that you don't get returned");
    std::cout << parseStringLiteral(example.begin(), example.end());
}
