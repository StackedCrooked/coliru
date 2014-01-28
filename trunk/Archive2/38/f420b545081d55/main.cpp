// #include "stdafx.h"
#include <iostream>
#include <cmath> // <math.h>
#include <ctime> // <time.h>
#include <iomanip>
#include <array>
#include <algorithm>

//using namespace std;

const int AS = 6 ;

// if <array> was not included just for fun
// using array_type = std::array< std::array< int, AS > > ;

// otherwise
using array_type = int[AS][AS] ; // type of the array
// archaic syntax: typedef int array_type[AS][AS] ;

void FillingRandomly( /*int * */ array_type& ); // we get a reference to the array
void printing( /*int * */ const array_type& );

//int c;

int main()
{
    // int funny = 0;
	// int timpa = 0;
	// int counter = 0;

	int Array[AS][AS];
	std::srand(time(0));
	FillingRandomly(Array);

	std::cout << "The unsorted array is\n\n" ; // << endl << endl;

	printing(Array);

	std::cout << "\n\nThe sorted array is\n\n" ;
}

void FillingRandomly( array_type& arr )
{
    for( auto& row : arr )
        for( int& v : row ) v = std::rand()%87 +12 ;
}

void printing( const array_type& arr )
{
    for( const auto& row : arr )
    {
        for( int v : row ) std::cout << std::setw(3) << v ;
        std::cout << '\n' ;
    }
}
