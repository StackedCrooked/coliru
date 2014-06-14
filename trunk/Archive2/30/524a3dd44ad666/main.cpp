#include <cstddef>
#include <limits>
#include <ctime>
#include <cstdlib>

template< typename Integral >
std::size_t findZeroSky(Integral x, Integral base = 10)
{
    std::size_t counter = 0;

	while ( x != 0 )
	{
		counter++;
		if ( x%base == 0 )
			return counter;
		x /= base;
	}

	return std::numeric_limits<std::size_t>::max();
}

template< typename Integral >
std::size_t findZeroArcoth(Integral x, Integral base = 10)
{
	auto d = std::div(x, base);
	for (std::size_t counter = 0; d.quot != 0 ; ++counter)
	{
		if( d.rem == 0 )
			return counter;

		d = std::div(d.quot, base);
	}

	return -1;
}

template< typename Func >
clock_t test( Func f, unsigned testN = 10'000'000 )
{
	auto c = clock();
	srand(time(nullptr));
	for( unsigned i = 0; i != testN; ++i )
		f( rand() );

	return clock() - c;
}

#include <iostream>

int main()
{
	std::cout << "Test....\n";

	auto a = 1. * test( []( auto i ){ return findZeroArcoth(i); } ) / CLOCKS_PER_SEC;
	std::cout << "Arcoth:   " << a << '\n';
	auto b = 1. * test( []( auto i ){ return findZeroSky   (i); } ) / CLOCKS_PER_SEC;
	std::cout << "Skymosh0: " << b << '\n';
}
