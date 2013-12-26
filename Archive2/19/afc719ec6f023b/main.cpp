#include <iostream>
#include <bitset>
#include <climits>

template <typename TTo, typename T>
TTo cowboy_cast ( const T& cow) {
	union u {
		T cow;
		TTo boy;
	};
	return u{cow}.boy;
}

int main () {
    float f = 5.25f;
    int i = cowboy_cast<int>( f );
    static_assert( sizeof( f ) * CHAR_BIT == 32, "Woo!" );
    std::bitset<sizeof( f ) * CHAR_BIT> bits( i );
    std::cout << "Bits: " << bits << std::endl;
    std::cout << "Single-Precision Float: " << cowboy_cast<float>( i ) << std::endl;
}