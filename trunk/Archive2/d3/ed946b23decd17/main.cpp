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

struct insert_ {
    typedef void result_type;
    
    template <typename S, typename T>
      void operator()(S& set, T const& v) const {
          set.insert(v);
      }
};

bool cond( long r ) { return r % 2 == 0 ; }

int main() {
    using namespace boost::lambda;
    std::set<long> myResults;
    work( 
        if_then( bind(&cond,_1) , bind(insert_(), var(myResults), _1) ) );

    BOOST_FOREACH( long r, myResults )
        std::cout << r << "\n";
}