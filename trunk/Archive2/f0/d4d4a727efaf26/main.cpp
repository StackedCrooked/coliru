#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

template <class T>
class Matrix
{    
	//Our non member functions.
public:	
    Matrix & operator++();
	Matrix & operator--();
    Matrix operator++(int); // post increment forms take an int arg
    Matrix operator--(int);

    //........
    
    //Overloaded increment operator, postfix.
};

template <class T>
Matrix<T> & Matrix<T>::operator++()
{
    std::cout << "increment" << std::endl;
 	return *this;
}

//Decrement overloaded operator, postfix.
template <class T>
Matrix<T> & Matrix<T>::operator--()
{
    std::cout << "decrement" << std::endl;
	return *this;

}

int main()
{
    Matrix<int> m;
    ++m;
    --m;
}
#endif