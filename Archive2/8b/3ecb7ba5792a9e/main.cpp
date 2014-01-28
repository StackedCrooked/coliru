#include <iostream>

struct A 
{ 
    A( int ii ) : i(ii) { std::cout << "constructor\n" ; }
    A( const A& that ) : i(that.i) { std::cout << "copy constructor\n" ; }
    ~A() { i = -999999 ; std::cout << "destructor\n" ; }
    int i ;
};

const A& returnarg_bad( const A& r1 )
{
    return r1;
}

A returnarg_good( const A& r1 )
{
    return r1;
}

int main()
{
    {
    	const A& r = returnarg_bad(2);
    	std::cout << r.i << '\n' ;
    }
    std::cout << "-----------------------\n" ;
    {
        const A& r = returnarg_good(2);
    	std::cout << r.i << '\n' ;
    }
}
