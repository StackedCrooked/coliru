#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <iterator>
#include <iostream>
#include <vector>

template<size_t N>
struct select_element
{
    template<class T>    
    typename T::reference operator()(T& source) const { return source[N]; }
};

int main()
{
    using boost::adaptors::transformed;

    std::vector<std::vector<double>> input { {1, 30, 5}, {4, 10, 4}, {2, 9, 10 } };

    boost::sort(input | transformed(select_element<0>()));
    boost::sort(input | transformed(select_element<1>()));
    boost::sort(input | transformed(select_element<2>()));
    boost::copy(
        input[0],
        std::ostream_iterator<double>(std::cout, ","));
    std::cout << std::endl;
    boost::copy(
        input[1],
        std::ostream_iterator<double>(std::cout, ","));
    std::cout << std::endl;
    boost::copy(
        input[2],
        std::ostream_iterator<double>(std::cout, ","));
    std::cout << std::endl;
    return 0;
}