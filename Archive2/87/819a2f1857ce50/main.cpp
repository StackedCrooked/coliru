#include <iostream>
#include <type_traits>
#include <map>

template< int C > struct Test 
{
    // blah<ENABLER> is a dependant name; subject to the two phase lookup rule
    // resolution of dependant name 'blah<ENABLER>' is postponed to phase two
    template < bool ENABLER = (C==1) > // makes ENABLER a dependant name
    typename std::enable_if< ENABLER, bool >::type blah() const{ return false ; } 
};

int main()
{
    std::map< int, Test<1> > meh1 { { 1, {} } }; // fine
    
    meh1[1].blah() ; // fine; Test<1>::blah() ;
    
    std::map< int, Test<0> > meh0 { { 0, {} } }; // fine
    
    // meh0[0].blah() ; // *** error: ‘Test<0>’ has no member named ‘blah’
}