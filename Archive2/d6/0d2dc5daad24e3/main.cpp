#include <bitset>
#include <cassert>
#include <limits>

template <std::size_t N>
using fits_in_ull = std::integral_constant<bool, N <= std::numeric_limits<unsigned long long>::digits>;

template <std::size_t N>
unsigned long long div_impl(std::bitset<N>& Q, unsigned long long divisor, std::false_type)
{
    assert (divisor != 0); // ?

	unsigned long long R = 0;

	for (std::size_t i = N; i--;) // Go through every bit of Q in reverse order
	{
		R = (R << 1) + Q[i]; // make room for next bit, then set LSB to Q[i]
		Q[i] = (R >= divisor); // Set Q to equal 1 if R has an overflow
		if (Q[i]) // If that's the case..
			R -= divisor; // subtract
	}

	return R;
}

template <std::size_t N>
unsigned long long div_impl(std::bitset<N>& b, unsigned long long divisor, std::true_type)
{
	auto u = b.to_ullong();
	b = u/divisor;
	return u%divisor;
}

template <std::size_t N>
unsigned long long div(std::bitset<N>& b, unsigned long long divisor)
{
	return div_impl(b, divisor, fits_in_ull<N>{});
}

// -----------------------------------------------------------------------------------
// I/O:

#include <algorithm>
#include <ios>

template <std::size_t N2, std::size_t N>
std::bitset<N2> copy( std::bitset<N> const& b )
{
	std::bitset<N2> r;

	for (std::size_t i = 0; i != std::min(N, N2); ++i)
		r[i] = b[i];

	return r;
}

template <std::size_t shift, std::size_t N>
char* shifted_print_impl(std::bitset<N>& b, char* p, char const* digits)
{
	do
	{
		*p++ = digits[copy<shift>(b).to_ulong()];
		b >>= shift;
	}
	while (b.any());
	return p;
}

template <typename OutputIterator, std::size_t N>
OutputIterator print( OutputIterator out, std::ios_base& stream, std::bitset<N> bitset )
{
	auto showpos = stream.flags() & std::ios_base::showpos;

	if (showpos)
		*out++ = '+';

	if (bitset.none())
	{
		*out++ = '0';
		return out;
	}

	auto basefield = stream.flags() & std::ios_base::basefield;
	auto uppercase = stream.flags() & std::ios_base::uppercase;
	auto showbase  = stream.flags() & std::ios_base::showbase ;

	static char const digits_lower[] = "0123456789abcdef";
	static char const digits_upper[] = "0123456789ABCDEF";
	char const* const digits = uppercase? digits_upper : digits_lower;

	char output[N/3 + 2];
	char* p = output;

	if (basefield == std::ios_base::dec)
	{
		do
			*p++ = digits[div(bitset, 10)];
		while (bitset.any());
	}
	else if (basefield == std::ios_base::hex)
	{
		if (showbase)
		{
			*out++ = '0';
			*out++ = (uppercase? 'X' : 'x');
		}

		p = shifted_print_impl<4>(bitset, p, digits);
	}
	else /*if (basefield == std::ios_base::oct)*/
	{
		if (showbase)
			*out++ = '0';

		p = shifted_print_impl<3>(bitset, p, digits);
	}

	std::reverse_copy( output, p, std::ostreambuf_iterator<char>(out) );

	return out;
}

// ------------------------------------------------------------
// Demonstration:

#include <functional>
#include <iostream>
#include <random>

//! Schnell skizziert, geht natürlich deutlich schöner
template <std::size_t N,
          typename URNG>
std::bitset<N> random_bitset( URNG&& eng, std::size_t bits_per_extract )
{
	std::bitset<N> rval;

	auto const loop_count = (N + bits_per_extract - 1) / bits_per_extract;

	std::size_t counter = 0;
	for (unsigned i = 0; i != loop_count; ++i )
	{
		auto u = eng();
		do
			rval[counter++] = (u >>= 1) & 1;
		while (counter % bits_per_extract && counter != N);
	}

	return rval;
}

int main()
{
	std::mt19937_64 engine( std::random_device{}() );

	for (int i = 0; i != 20; ++i)
	{
		auto b = random_bitset<128>(engine, 64);
		std::cout << std::hex << std::uppercase;
		print(std::ostreambuf_iterator<char>{std::cout}, std::cout, b) = '\n';
	}
}