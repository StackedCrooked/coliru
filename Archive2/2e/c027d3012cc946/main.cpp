#include <iostream>
#include <iomanip>
#include <boost/multi_array.hpp>

int main()
{
    typedef boost::multi_array<double,3> array_type;
    // 0-based, column-major 3D array 3x4x2
    array_type A(boost::extents[3][4][2],
                 boost::fortran_storage_order());

    A[0][0][0] = 0.000;
    A[0][0][1] = 0.001;
    A[1][0][0] = 0.100;

    std::cout << std::fixed << std::setprecision(3)
              << "first element in underlying storage is " << A.data()[0] << '\n'
              << "second element in underlying storage is " << A.data()[1] << '\n';

}
