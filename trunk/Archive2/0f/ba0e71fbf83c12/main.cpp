#include <iostream>
#include <regex>

int main()
{
    std::string const s{ "true" };
    std::regex const r{ R"r((true|false)|([a-zA-Z]+))r" };
    std::smatch m;
    if(std::regex_search(s, m, r))
    {
        for(std::size_t i{ 1 }; i < m.size(); ++i)
        {
            if(m[i].matched)
            { std::cout << "matched group " << i << "; " << std::endl; }
        }
    }
}
