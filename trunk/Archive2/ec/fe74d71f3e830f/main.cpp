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

void my_insert(std::set<long>& values, long r )
{
    values.insert(r);
}

int main() {
    using namespace boost::lambda;
    std::set<long> myResults;
    work( 
        if_then( bind(&cond,_1) , boost::lambda::bind(&my_insert,var(myResults),_1) ) );

    BOOST_FOREACH( long r, myResults )
        std::cout << r << "\n";
}