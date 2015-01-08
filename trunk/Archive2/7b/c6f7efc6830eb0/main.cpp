#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>    

template<typename T, typename U>
void assign(boost::numeric::ublas::matrix<T> & m, std::size_t row, std::size_t col, U const & data)
{
    m.resize(std::max(m.size1(), row+1), std::max(m.size2(), col+1));
    m(row, col) = data;
}

int main () 
{
    boost::numeric::ublas::matrix<double> m;
    
    assign(m, 0, 0, 9);  //m(0,0) = 9; 
    assign(m, 3, 2, 20); //m(3,2) = 20
    
    std::cout << m << std::endl; //prints : [4,3]((9,0,0),(0,0,0),(0,0,0),(0,0,20))
    return 0;
}