#include <map>
#include <string>

bool less_ic(std::string const& a, std::string const& b)
{
    return a<b; // TODO
}

int main()
{
    std::map<std::string, int, decltype(&less_ic)> map(less_ic);
}
