#include <boost/range/any_range.hpp>
#include <boost/range/join.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>

int main() {
    std::vector<int> const aaa { 1,1,1,4,5,5,9,42,42,42,42,42,42 };

    boost::any_range<int, boost::forward_traversal_tag, int> r;
    for (size_t i = 0; i < aaa.size(); ++i)
        r = boost::join(r, boost::equal_range(aaa, i));

    boost::copy(r, std::ostream_iterator<int>(std::cout << "result: ", " "));
}
