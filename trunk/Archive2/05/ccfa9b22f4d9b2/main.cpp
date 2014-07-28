#include <iostream>
#include <cmath>
using std::pow;

template <typename T, const int N>
class TVectorND
{
public:
    //Other things
    const T & operator[] (size_t n) const { return data[n]; }
    T & operator[] (size_t n) { return data[n]; }
    T data[N];
};

template <typename T, const int N, const int M>
class TMatrixNxM
{
public:
    //Other things
    TVectorND<T, M> data[N];
    const TVectorND<T, M> & operator[] (size_t n) const { return data[n]; }
    TVectorND<T, M> & operator[] (size_t n) { return data[n]; }
};



template <typename T>
T determinant(const TMatrixNxM<T, 1, 1> &par_value)
{
    T result = T(0);
    result = par_value[0][0];    
    return result;
}

template <typename T>
T determinant(const TMatrixNxM<T, 2, 2> &par_value)
{
    T result = T(0);
    result = par_value[0][0] * par_value[1][1] - par_value[0][1] * par_value[1][0];
    return result;
}

template <typename T>
T determinant(const TMatrixNxM<T, 3, 3> &par_value)
{
    T result = T(0);
    result = par_value[0][0] * (par_value[1][1] * par_value[2][2] - par_value[1][2] * par_value[2][1]) - par_value[0][1] * (par_value[1][0] * par_value[2][2] - par_value[1][2] * par_value[2][0]) + par_value[0][2] * (par_value[1][0] * par_value[2][1] - par_value[1][1] * par_value[2][0]);
    return result;
}

template <typename T, const int N>
T cofactor(const TMatrixNxM<T, N, N> &par_value, int par_i, int par_j);

template <typename T, const int N>
T determinant(const TMatrixNxM<T, N, N> &par_value)
{
    static_assert(N >= 4, "Default determinant called for N<4");
    T result = T(0);

    //i loops through 0 to N-1, k is arbitrarily chosen to be 0
    for (int i = 0; i < N; i++)
    {
        result += par_value[i][0] * cofactor(par_value, i, 0);
    }
    return result;
}

template <typename T, const int N>
T cofactor(const TMatrixNxM<T, N, N> &par_value, int par_i, int par_j)
{
    T result = T(0);

    //Construct the new matrix, without the i-th row j-th column
    TMatrixNxM<T, N - 1, N - 1> newMatrix;

    int k = 0;

    for (int i = 0; i < N - 1; i++)
    {
        int l = 0;

        if (k == par_i) k++;

        for (int j = 0; j < N - 1; j++)
        {
            if (l == par_j) l++;

            newMatrix[i][j] = par_value[k][l];

            l++;
        }

        k++;
    }

    result = pow(-1, (par_i + 1) + (par_j + 1)) * determinant(newMatrix); //I have to add +1 to i and j since I started from 0

    return result;
}

int main(){
    TMatrixNxM<float, 4, 4> mat1 = { 0 };
    TMatrixNxM<float, 3, 3> mat2 = { 0 };
    TMatrixNxM<float, 2, 2> mat3 = { 0 };
    TMatrixNxM<float, 1, 1> mat4 = { 0 };
    //Set values
    float det = determinant(mat1);
    det = determinant(mat2);
    det = determinant(mat3);
    det = determinant(mat4);
}