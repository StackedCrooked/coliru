#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/tuple_tie.hpp>
#include <boost/fusion/include/list_tie.hpp>
#include <boost/phoenix.hpp>
#include <vector>
#include <iostream>

namespace fus = boost::fusion;
using namespace boost::phoenix::arg_names;

int main() {
    std::vector<int> v { 1,2,3,4,5,6 };

    fus::for_each(fus::vector_tie(v[0], v[1], v[2], v[3], v[4], v[5]), std::cout << arg1 << ", ");
    std::cout << "\n";

    fus::for_each(fus::list_tie  (v[0], v[1], v[2], v[3], v[4], v[5]), std::cout << arg1 << ", ");
    std::cout << "\n";

    fus::for_each(fus::tie       (v[0], v[1], v[2], v[3], v[4], v[5]), std::cout << arg1 << ", ");
    std::cout << "\n";
}
