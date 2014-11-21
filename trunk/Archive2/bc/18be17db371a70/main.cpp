#include <boost/phoenix.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <iostream>
#include <vector>

struct pnt {
    char _name;
    int _type;
    bool _aux;
};

using boost::phoenix::bind;
using boost::phoenix::arg_names::arg1;

int main()
{
    std::vector<pnt> v{ pnt{'a',1,false}, pnt{'b',2,true} };

    boost::for_each(v, std::cout << bind(&pnt::_type, arg1) << "\n");
}
