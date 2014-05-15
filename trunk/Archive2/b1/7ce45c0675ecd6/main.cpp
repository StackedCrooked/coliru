
///////////////////////
// Simple2DMatrixD.h //
///////////////////////

#include <cstring>
#include <algorithm>
#include <iostream>

class Simple2DMatrixD {
    
    int     numRows;
    int     numCols;
    double *dataArray;
public:   
    Simple2DMatrixD(int const n, int const m);
    virtual ~Simple2DMatrixD() {delete [] dataArray; }
    Simple2DMatrixD(Simple2DMatrixD const &other);
    Simple2DMatrixD& assign(Simple2DMatrixD const &matrixB);
    Simple2DMatrixD& sum(Simple2DMatrixD const &other);
    Simple2DMatrixD& operator=(Simple2DMatrixD const &rhs);
    Simple2DMatrixD operator+(Simple2DMatrixD const &rhs) const;
    double& operator()(int const i, int const j);
    void print();
};

Simple2DMatrixD::Simple2DMatrixD(int const n, int const m) : numRows(n), numCols(m), dataArray(new double[numRows * numCols]) {}
Simple2DMatrixD::Simple2DMatrixD(Simple2DMatrixD const &other) : numRows(other.numRows), numCols(other.numCols), dataArray(new double[numRows * numCols])
{
    memcpy(dataArray, other.dataArray, numRows * numCols * sizeof(double));
}
Simple2DMatrixD& Simple2DMatrixD::operator=(Simple2DMatrixD const &rhs)
{
    this->assign(rhs);
    return *this;
}
Simple2DMatrixD& Simple2DMatrixD::assign(Simple2DMatrixD const &other)
{
    std::copy(other.dataArray, other.dataArray + (other.numRows * other.numCols), dataArray);
    return *this;
}
Simple2DMatrixD& Simple2DMatrixD::sum(Simple2DMatrixD const &other)
{
    // TODO REPLACE WITH COMPAREDIMENSION FUNCTION
    if((this->numRows == other.numRows) && (this->numCols == other.numCols)) {
        for(auto i(0); i < (numRows * numCols); ++i) dataArray[i] += other.dataArray[i];
   } else {
        throw " Dimensions does not match!";
   }
   return *this;
}
Simple2DMatrixD Simple2DMatrixD::operator+(Simple2DMatrixD const &rhs) const
{
    Simple2DMatrixD tmp(rhs);
    tmp.sum(rhs);
    return tmp;
}

double& Simple2DMatrixD::operator()(int const i, int const j)
{
    return dataArray[i + j * numRows];    
}

void Simple2DMatrixD::print()
{
    for(auto i(0); i < numRows; ++i) {
        for(auto j(0); j < numCols; ++j) {
            std::cout << (*this)(i, j) << "   ";    
        }    
        std::cout << std::endl;
    }    
}


int main()
{
    Simple2DMatrixD A(2, 2);
    A(0,0) = 1.0; A(0,1) = 2.0; A(1,0) = 3.0; A(1,1) = 4.0;
    Simple2DMatrixD B(A);
    Simple2DMatrixD C = A + B;  
    C.print();
    
    return 0;
}