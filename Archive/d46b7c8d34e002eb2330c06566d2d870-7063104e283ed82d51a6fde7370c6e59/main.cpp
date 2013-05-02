#include <iostream>
#include <ctime>
#include <random>
#include <memory>

///<summary>
/// Off the edge we go~
///</summary>
template <typename TTo, typename T>
TTo suicide_cast ( const T& gun ) {
	typedef TTo* russian;
	std::srand( time( nullptr ) );
	int bullets = std::rand();
	void* roulette = (void*)( ((char*)std::addressof( gun )) + bullets );
	
	return *russian( roulette );
}


int main (  ) {
    int emo = 0xDEADBEEF;
    short ohgod = suicide_cast<short>( emo );
    std::cout << ohgod << std::endl;
}