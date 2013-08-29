#include <iostream>
#include <boost/version.hpp>
using namespace std;
 struct A {
  int i = 42;
} a;
int main()
{
    A a;
    cout << a.i << '\n';
        cout << ( BOOST_VERSION / 100000 ) << "." << ( BOOST_VERSION / 100 % 1000 ) << "." << BOOST_VERSION % 100;
}