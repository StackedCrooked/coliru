#include <map>
#include <string>

struct less_ic
{
    bool operator()(std::string const& a, std::string const& b) const
    {
        return a<b; // TODO
    }
};

int main()
{
    std::map<std::string, int, less_ic> map;
}
