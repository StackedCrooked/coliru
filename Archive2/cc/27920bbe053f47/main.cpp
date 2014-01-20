#include <array>
using namespace std;

template <class T, unsigned int Rows, unsigned int Columns>
class Matrix2D
{
private:
    array<array<T,Columns>, Rows> m_Matrix;

public:
    Matrix2D() {}

    array<T,Columns>& operator[](unsigned int row)       { return m_Matrix[row]; } ;
    const array<T,Columns>& operator[](unsigned int row) const { return m_Matrix[row]; } ;

    template <class T1, unsigned int Rows1, unsigned int Columns1>
    friend Matrix2D<T1,Rows1,Columns1> operator+ (const Matrix2D<T1,Rows1,Columns1> &lhs, const Matrix2D<T1,Rows1,Columns1> &rhs);

    template <class T1, unsigned int Rows1, unsigned int Columns1>
    friend Matrix2D<T1,Rows1,Columns1> operator* (const Matrix2D<T1,Rows1,Columns1> &lhs, const Matrix2D<T1,Rows1,Columns1> &rhs);
};

int main()
{}
