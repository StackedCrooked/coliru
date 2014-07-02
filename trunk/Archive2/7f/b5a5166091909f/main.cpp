#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;

int main()
{

  using namespace boost::numeric::ublas;
  matrix<double> a (4, 3);
  a <<= 0,1,2,
        3,4,5,
        6,7,8,
        9,10,11;
 


  matrix<double> b (2,3);
  b <<= 20,21,22,
        23,24,25;


  cout << "matrix a : " << a << endl;
  cout << "matrix b : " << b << endl;

  //alternative 1
  project(a, slice(/*start*/0,/*stride*/2,/*size*/2), slice(0,1,3) ) = b;

  //alternative 2
  //subslice(a, 0, 2, 2 ,  0, 1, 3 ) = b;

  //alternative 3
  //indirect_array<> rows(2);
  //rows[0]=0; rows[1]=2;
  //matrix_indirect<matrix<double>, indirect_array<> >(a,rows,indirect_array<>::all())=b;
  //you could also use
  //indirect_array<> columns(3);
  //columns[0]=0; columns[1]=1; columns[2]=2;
  //matrix_indirect<matrix<double>, indirect_array<> >(a,rows,columns)=b;
  
  cout << "matrix a : " <<  a << endl;

  return 0;
}

