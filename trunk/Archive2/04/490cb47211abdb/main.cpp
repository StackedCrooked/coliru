#include <boost/function.hpp>
#include <boost/phoenix/phoenix.hpp>

#include <boost/foreach.hpp>
#include <iostream>
#include <set>

void work(  boost::function<void(long)> doAction ) {
    long results[] = { 2, 5, 4 };
    BOOST_FOREACH( long r, results )
        doAction( r );
}

bool cond( long r ) { return r % 2 == 0 ; }
BOOST_PHOENIX_ADAPT_FUNCTION(bool, cond_, cond, 1);

namespace phx=boost::phoenix;

int main() {
    using phx::arg_names::_1;
    std::set<long> myResults;
    work( 
        if_(cond_(_1))
        [
            phx::insert(phx::ref(myResults),_1)
        ]
        );

    BOOST_FOREACH( long r, myResults )
        std::cout << r << "\n";
}