#include <iostream>
#include <string>
#include <regex>
#include <map>
 
std::string format(const std::string& format, const std::map<std::string, std::string>& map)
{
    using std::sregex_token_iterator;
    
    static const auto kDirective = std::regex{R"((\{[_[:alpha:]][_[:alnum:]]*\}))"};
    static const auto kVarName = std::regex{R"(\{([_[:alpha:]][_[:alnum:]]*)\})"};
    
    std::string ret;
    auto f = [&ret, map] (const sregex_token_iterator::value_type& sm)
    {   
        std::smatch m;
        if (std::regex_match(sm.str(), m, kVarName))
        {
            auto p = map.find(m[1]);
            if (map.end() == p)
                ret += m[0];
            else
                ret += p->second;
        }
        else
        {
            ret += sm.str();
        }
    };

    std::for_each(sregex_token_iterator{begin(format), end(format), kDirective, {-1, 1}},
                  sregex_token_iterator{},
                  f);
                  
    return ret;
}
 
int main()
{
    std::cout << format("aaa {a1} {a2} {{a3} bbb", {{"a1", "111"}, {"a2", "222"}}) << std::endl; 
    // expected : aaa 111 222 {{a3} bbb
    // result : aaa 111 222 {a3} bbb
    
    std::cout << format("aaa {} {{}} {a1} bbb}", {{"a1", "111"}}) << std::endl;
    // expected : aaa {} {{}} 111 bbb}
    return 0;
}