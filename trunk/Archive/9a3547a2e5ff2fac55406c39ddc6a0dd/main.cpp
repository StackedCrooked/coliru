#include <fstream>
#include <iostream>
#include <string>


template<unsigned size>
struct square_matrix
{
    square_matrix() : data() {}
    
    typedef int Data[size][size];
    Data data;
};

    
template<unsigned size>
struct strassen
{    
    typedef square_matrix<size> matrix;
    
    void strassen_matrix_multiplication(const matrix & , const matrix & , const matrix & )
    {
    }
};


template<>
struct strassen<1u>
{
    typedef square_matrix<1> matrix;
    
    void strassen_matrix_multiplication(const matrix &, const matrix &, const matrix &) {}
};


template<>
struct strassen<0u>
{
    void strassen_matrix_multiplication() {}
};


int main()
{
    strassen<3u> s;
    strassen<3u>::matrix arr;
    s.strassen_matrix_multiplication(arr, arr, arr);
}