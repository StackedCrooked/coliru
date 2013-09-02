// Endian.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cassert>
#include <cmath>

template< int >
struct TypeForBytes;

template <>
struct TypeForBytes< 1 > { typedef unsigned char Type; };

template <>
struct TypeForBytes< 2 > { typedef unsigned short Type; };

template <>
struct TypeForBytes< 4 > { typedef unsigned int Type; };


template<typename T, int N>
struct ByteSwapper
{
    static T DoSwap( const T & acc, const T & src )
    {
        return ByteSwapper< T, N - 1>::DoSwap( ( acc << 8 ) | ( src & 0xff ), src >> 8 );
    }
};

template <typename T>
struct ByteSwapper< T, 0 >
{
    static T DoSwap( const T & acc, const T & src )
    {
        assert( src == 0 );
        return acc;
    }
};

template <typename T>
struct Swapper
{
    enum { Bytes = sizeof( T ) };
    typedef typename TypeForBytes< Bytes >::Type ConvType;

    Swapper( T data )
    {
        m_Data = ByteSwapper< ConvType, Bytes >::DoSwap(
            ConvType(),
            *reinterpret_cast< ConvType* >( &data ) );
    }

    ConvType m_Data;

};

int main(int argc, char* argv[])
{
    int x = 0x12345678;

    Swapper< int > swapper( x );
    assert( swapper.m_Data == 0x78563412 );

    float y = 3.14f;

    Swapper<float> floatSwapper( y );
    Swapper<unsigned int> secondSwapper( floatSwapper.m_Data );
    assert( fabs( *reinterpret_cast< float* >( &secondSwapper.m_Data ) - 3.14f ) < 0.001f );

    std::cout << "Success\n";
    return 0;
}

