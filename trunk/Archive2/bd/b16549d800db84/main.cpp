#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <iostream>
#include <string>
#include <sstream>
 
int main()
{
boost::numeric::ublas::matrix<double> m;
std::cin >> m;
std::cout << "Printing matrix: ";
std::cout << m;
}
 