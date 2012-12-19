#include <initializer_list>
#include <iostream>
#include <utility>
#include <array>
#include <vector>
// GET OVER IT :3c
using namespace std;

template<typename T, size_t Rows, size_t Columns>
class matrix {
private:
    static_assert( !std::is_class<T>::value, "Matrixes can only be integral or floating types" );
	T array_[Rows][Columns];

public:
	const static size_t RowSize = Rows;
	const static size_t ColumnSize = Columns;

   matrix ( const T(&data)[Rows][Columns] ) {
		for ( size_t r = 0; r < Rows; ++r ) {
			for ( size_t c = 0; c < Columns; ++c ) {
				array_[ r ][ c ] = data[ r ][ c ];
			}
		}
    }

    int* operator[] (size_t index) {
		return array_[ index ];
    }

};

int main ( int argc, char* argv[] ) {
	char freeze;
	size_t c, r;
	//matrix<int,3,3> a( data );
	matrix<int,3,3> b( { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} } );

    for ( r = 0; r < b.RowSize; ++r ) {
		for ( c = 0; c < b.ColumnSize; ++c ) {
			std::cout << b[ r ][ c ];
		}
		std::cout << endl;
	}
}