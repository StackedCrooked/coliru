#include <iostream>
#include <boost/shared_ptr.hpp>

struct A
{
};
void F1( boost::shared_ptr< const A >& arg1 )
{
    std::cout << "f1 called" << std::endl ;
}
 
int main() {
	boost::shared_ptr< A > a1( new A() ) ;
	boost::shared_ptr< const A > a2( new A() ) ;
	boost::shared_ptr< const A > a3 = a1 ;
 
	F1( a2 ) ;
	//F1( a1 ) ;
    F1( a3 ) ;
	return 0;
}
