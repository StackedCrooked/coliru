#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

template <class T>
class Matrix
{    
	//Our non member functions.
	template<class T>
	friend Matrix<T> operator++(const Matrix<T> &,T);
	template<class T>
	friend Matrix<T> operator--(const Matrix<T> &, T);
	template<class U>
	friend Matrix<U> operator*(U n, Matrix<U> U);
	template<class U>
	friend Matrix<U> operator*(Matrix<U> m1, Matrix<U> m2);
    //........
    
    
    //Overloaded increment operator, postfix.
template <class T>
Matrix<T> operator++(const Matrix<T> & m, T)
{
    //Iterate through the matrix and add one to each element.
	//Then return the result.
	Matrix<T> current(m.getdimension());
	for (int i = 0; i < m.getdimension(); i++)
	{
		for (int j=0; j < m.getdimension(); j++)
		{
			current.matrixarr[i][j] = m.getnumber(i,j) + 1;
		}
	}
	return current;
}

//Decrement overloaded operator, postfix.
template <class T>
Matrix<T> operator--(const Matrix<T> & m, T)
{
	//Same as increment operator, only subtract one
	//from each element as you iterate through.
	Matrix<T> current(m.getdimension());
	for (int i = 0; i < current.dimension; i++)
	{
		for (int j=0; j < current.dimension; j++)
		{
			current.matrixarr[i][j] = m.getnumber(i,j) - 1;
		}
	}
	return current;

}