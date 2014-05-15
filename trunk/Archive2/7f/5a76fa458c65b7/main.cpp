#include <boost/function.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>

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
    using namespace boost::lambda;
    std::set<long> myResults;
    work( 
        if_then( bind(&cond,_1) , boost::lambda::bind(static_cast<std::pair<std::set<long>::iterator,bool> (std::set<long>::*) (const long&) >(&std::set<long>::insert),var(myResults),_1) ) );

    BOOST_FOREACH( long r, myResults )
        std::cout << r << "\n";
}