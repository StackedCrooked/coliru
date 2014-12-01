#include <iostream>
#include <iterator>
#include <map>

int main()
{
    auto source = std::map<std::string, int>{ {"cat", 1}, {"dog", 3} };
    auto target = std::map<std::string, int>{ {"cat", 1}, {"horse", 3} };
    
    auto s = source.rbegin();
    auto t = target.rbegin();
    while(s != source.rend() && t != target.rend())
    {
        if(t->first < s->first)
        {
            t = decltype(target)::reverse_iterator( target.insert(t.base(), *s) );
            ++t;
            ++s;
        }else if(s->first < t->first)
        {
            ++t; // or via lower_bound?
        }else
        {
            t->second += s->second;
            ++t;
            ++s;
        }
    }
    while(s != source.rend())
    {
        t = decltype(target)::reverse_iterator( target.insert(t.base(), *s) );
        ++s;
    }
    
    for(auto const& e : target)
    {
        std::cout << "{" << e.first << ", " << e.second << "}\n";
    }
}