#include <iostream>
#include <map>

int main()
{
    auto source = std::map<std::string, int>{ {"cat", 1}, {"dog", 3} };
    auto target = std::map<std::string, int>{ {"cat", 1}, {"horse", 3} };
    
    for(auto i = source.begin(); i != source.end(); ++i)
    {
        auto const hint = target.lower_bound(i->first);
        if(hint->first == i->first)
        {
            hint->second += i->second;
        }else
        {
            target.insert(hint, *i);
        }
    }
    
    for(auto const& e : target)
    {
        std::cout << "{" << e.first << ", " << e.second << "}\n";
    }
}