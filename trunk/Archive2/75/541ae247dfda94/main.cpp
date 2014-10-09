#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <string>
#include <iterator>
#include <iostream>
#include <vector>

typedef boost::variant<int, std::string> Container;

class IsBad : public boost::static_visitor<bool>
{
public:
    result_type operator()(int& t) const { return  t % 2; }
    result_type operator()(std::string& s) const { return s == "foo"; }
};

int main()
{
    IsBad isBad;
    
    std::vector<Container> v;
    v.push_back(Container(2));
    v.push_back(Container(4));
    v.push_back(Container("foo"));
    v.push_back(Container(1));
    
    std::vector<Container>::iterator it = std::find_if(v.begin(), v.end(), boost::bind(static_cast<bool(*)(IsBad&, Container&)>(&boost::apply_visitor), isBad, _1));
    
    std::cout << "Found at index: " << std::distance(v.begin(), it) << std::endl;    
}
