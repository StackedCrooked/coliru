#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <tuple>
#include <cassert>

namespace mpl=boost::mpl;


int main(){
    std::tuple<int, float, double> t{1, 2, 3};
    mpl::for_each<mpl::vector<int, double>>([&t](const auto& type){ std::get<std::decay_t<decltype(type)>>(t)++;});
    assert(std::get<0>(t) == 2);
    assert(std::get<1>(t) == 2);
    assert(std::get<2>(t) == 4);
    
    return 0;
}