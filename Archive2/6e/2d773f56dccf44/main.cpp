#include <iostream>

#include <boost/iterator/zip_iterator.hpp>

int main()
{
    using std::begin;
    using std::end;
    auto as = { 0, 2, 4, 6, 8, 10 };
    auto bs = { 1, 3, 5, 7, 9 };
    auto it = boost::make_zip_iterator(boost::make_tuple(begin(as), begin(bs)));
    auto const stop = boost::make_zip_iterator(boost::make_tuple(end(as), end(bs)));
    for(; it != stop; ++it) {
        std::cout << it->get<0>() << ' ' << it->get<1>() << '\n';
    }
}