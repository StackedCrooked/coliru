#include <iostream>
#include <utility>
#include <string>
 
#include <map>

class str
{
    public:
    str(const std::string& s, size_t pos, size_t len) : m_s(s, pos, len) {}
    
    bool operator<(const str& rhs) const
    {
        return m_s < rhs.m_s;
    }
    std::string m_s;
    
    str(const str&) = delete;
    str(str&&) = delete;
    str& operator=(const str&) = delete;
    str& operator=(str&&) = delete;
    
};

int main()
{
    std::map<str, str> m;
 
    std::string s = "we were here";
 
    // uses pair's piecewise constructor (overload 6)
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple(s, 3, 4),
              std::forward_as_tuple(s, 0, 2));
 
    for (const auto &p : m) {
        std::cout << p.first.m_s << " => " << p.second.m_s << '\n';
    }
}