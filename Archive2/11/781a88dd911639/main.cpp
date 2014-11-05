#include <utility>
#include <string>

struct strinfo;

namespace Math
{
    std::pair<double, std::string> calcSpeed(struct strinfo *, double, double) {return {0., ""};}
}

int main() 
{
    typedef std::pair<double, std::string> (*FuncChosen)(struct strinfo *si, double first, double second);
    FuncChosen p = Math::calcSpeed;
}
