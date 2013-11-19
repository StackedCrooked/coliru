#include <boost/variant.hpp>
#include <map>

class recursive_variant;

typedef boost::variant<int, float, std::string, recursive_variant> chamaeleon;

struct recursive_variant : public std::map<std::string, chamaeleon> {
    using super =  std::map<std::string, chamaeleon>;
    using super::super;
};

int main()
{
}
