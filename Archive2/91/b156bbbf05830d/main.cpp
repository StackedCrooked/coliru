#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/iterator/zip_iterator.hpp>

int main(int argc, char* argv[])
{
    int Array1 [] = { 9, 65, 87, 89, 888 };
    int Array2 [] = { 1, 13, 33, 49, 921 };
    int Array3 [] = { 22, 44, 66, 88, 110 };

    std::vector<int> v;
    
    std::for_each(
        boost::make_zip_iterator(boost::make_tuple(std::begin(Array1), std::begin(Array2), std::begin(Array3))),
        boost::make_zip_iterator(boost::make_tuple(std::end(Array1), std::end(Array2), std::end(Array3))),
        [&v](boost::tuple<int, int, int> const& t) {
            v.push_back(t.get<0>()); v.push_back(t.get<1>()); v.push_back(t.get<2>());
        }
    );
    
    std::partial_sort(begin(v), begin(v) + 5, end(v), std::greater<int>());
    std::copy(begin(v), begin(v) + 5, std::ostream_iterator<int>(std::cout, " "));

    return 0;
}