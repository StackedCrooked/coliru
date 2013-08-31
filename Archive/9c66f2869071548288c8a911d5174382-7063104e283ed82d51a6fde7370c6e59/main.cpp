#include <iostream>
#include <ctime>
#include <random>
#include <memory>

///<summary>
/// Click.... Click..... click..... click.....
///</summary>
template <typename TTo, typename T>
TTo roulette_cast ( const T& gun ) {
	typedef TTo* russian;
	std::srand( time( nullptr ) );
	int bullets = std::rand();
	void* roulette = (void*)( ((char*)std::addressof( gun )) + bullets );
	
	return *russian( roulette );
}


int main (  ) {
    int vladimir = 0xDEADBEEF;
    short ohgod = roulette_cast<short>( vladimir );
    std::cout << ohgod << std::endl;
}