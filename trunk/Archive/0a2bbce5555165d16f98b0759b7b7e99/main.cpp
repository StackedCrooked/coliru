#include <iostream>
#include <functional>
#include <vector>

using namespace std;

int main()
{
    // DECLARE LOCAL VARIABLES
    unsigned nPosition = 5;
    unsigned nLength = 5;
    std::vector<unsigned>vn_VectorA;
    unsigned *an_ArrayA = new unsigned[ nLength ];

    // FILL vn_VectorA WITH DECIMAL VALUE OF "HelloWorld!!!"
    vn_VectorA.push_back( 72 );     // H
    vn_VectorA.push_back( 101 );    // e
    vn_VectorA.push_back( 108 );    // l
    vn_VectorA.push_back( 108 );    // l
    vn_VectorA.push_back( 111 );    // o
    vn_VectorA.push_back( 87 );     // W
    vn_VectorA.push_back( 111 );    // o
    vn_VectorA.push_back( 114 );    // r
    vn_VectorA.push_back( 108 );    // l
    vn_VectorA.push_back( 100 );    // d
    vn_VectorA.push_back( 33 );     // !
    vn_VectorA.push_back( 33 );     // !
    vn_VectorA.push_back( 33 );     // !

    // Copy the desire values of vn_VectorA to an_ArrayA
    for(unsigned nCopyIndex = nPosition, nArrayAIndex = 0; nArrayAIndex != nLength; nArrayAIndex ++, nCopyIndex ++ )
    {
        an_ArrayA[ nArrayAIndex ] = vn_VectorA[ nCopyIndex ];
        std::cout << an_ArrayA[ nArrayAIndex ] << ' ';
    }
}