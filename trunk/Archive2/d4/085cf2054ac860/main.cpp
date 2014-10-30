#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <iterator>
#include <algorithm>

#include <boost/tuple/tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>

int main ()
{
    std::vector<double> v1{0.0, 
                           std::numeric_limits<double>::quiet_NaN(), 
                           std::numeric_limits<double>::quiet_NaN(), 
                           3.3,
                           4.4};
    std::vector<int> v2{0, 1, 2, 3, 4};
    
    auto result = std::remove_if(boost::make_zip_iterator(boost::make_tuple(v1.begin(), v2.begin())),
                                 boost::make_zip_iterator(boost::make_tuple(v1.end(),   v2.end())),
                                 [](boost::tuple<double, int> const& elem) {
                                     return std::isnan(boost::get<0>(elem));
                                 });
    v1.erase(boost::get<0>(result.get_iterator_tuple()), v1.end());
    v2.erase(boost::get<1>(result.get_iterator_tuple()), v2.end());
    
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<decltype(v1)::value_type>(std::cout, "\n"));
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<decltype(v2)::value_type>(std::cout, "\n"));
}
