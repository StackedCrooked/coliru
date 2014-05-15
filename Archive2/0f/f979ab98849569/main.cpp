#include <boost/phoenix.hpp>
#include <boost/function.hpp>

#include <boost/foreach.hpp>
#include <iostream>
#include <set>

void work(  boost::function<void(long)> doAction ) {
    long results[] = { 2, 5, 4 };
    BOOST_FOREACH( long r, results )
        doAction( r );
}

bool cond( long r ) { return r % 2 == 0 ; }

int main() {
    namespace phx = boost::phoenix;
    using namespace phx::placeholders;
    
    std::set<long> myResults;
    work( 
        if_(phx::bind(cond, _1)) [ phx::insert(phx::ref(myResults), _1) ] );

    BOOST_FOREACH( long r, myResults )
        std::cout << r << "\n";
}