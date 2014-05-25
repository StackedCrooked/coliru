#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <iostream>
#include <iterator>
#include <vector>

struct Term
{
    int ix;
    double f;
};

int main()
{
    using namespace boost::adaptors;
    
    auto terms = std::vector<Term>{ {0, 0.1}, {1, 1.1}, {2, 0.8}, {3, 1.2}, {4, 0.9} };
    auto termIxVector = terms 
        | filtered([](auto x){ return x.f < 1.0; }) // select
        | transformed([](auto y){ return y.ix; })   // project
    ;    
    
    boost::copy(termIxVector, std::ostream_iterator<int>(std::cout, ","));    
}
