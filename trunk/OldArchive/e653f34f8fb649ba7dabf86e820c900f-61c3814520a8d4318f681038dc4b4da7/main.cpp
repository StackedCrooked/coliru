#include <iostream>
#include <boost/version.hpp>
using namespace std;
 
int main()
{
   
        cout << ( BOOST_VERSION / 100000 ) << "." << ( BOOST_VERSION / 100 % 1000 ) << "." << BOOST_VERSION % 100;
}