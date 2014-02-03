#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <stdexcept>

template<typename InputIt>
std::basic_string<typename InputIt::value_type> parseStringLiteral(InputIt &st, InputIt en)
{
    std::vector<typename InputIt::value_type> result;
    
    for ( ; st != en; ++st) {
        if (*st == '\\') {
            if (++st == en)
                throw std::exception();  // hack
            
            switch (*st)
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
        }
        else if (*st == '"')
        {
            return std::string(result.begin(), result.end());
        }
        else
        {
            result.push_back(*st);
        }
    }
    // Ran out of input without seeing closing doublequote
    throw std::exception();
}

int main()
{
    std::string example("This is a string literal with tab:\\t and newline:\\n!\" and stuff after the closing quote that you don't get returned");
    auto it = example.begin();
    std::cout << parseStringLiteral(it, example.end());
    
    std::istream_iterator<char> in(std::cin);
    std::cout << parseStringLiteral(in, std::istream_iterator<char>());
    // 'it' points to closing quote here
}
