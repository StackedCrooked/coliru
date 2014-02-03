#include <array>
#include <iostream>

int main()
{
    std::array<unsigned int, 4> trans_val_1 {} ;
    for( auto v : trans_val_1 ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    std::array<unsigned int, 4> xor_result_arr { { 0, 1, 2, 3 } } ; // nested braces are required here
	
    // nested braces are not required here, but it is probably a good idea to put them in anyway
    // some compilers may baulk without it
	trans_val_1 = { { xor_result_arr[0], xor_result_arr[1], xor_result_arr[2], xor_result_arr[3] } };

	// or simply use normal assignment
	trans_val_1 = xor_result_arr;
    
    for( auto v : trans_val_1 ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
