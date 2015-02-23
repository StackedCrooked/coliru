
#include <cstdint>
#include <iostream>

template<typename T>
struct bitset
{
    constexpr bitset(T bits) :
		_bits{bits}
	{}

	constexpr bool operator[](std::size_t i) const
	{
		return (_bits >> i) & 0x1;
	}
private:
	T _bits{0};
};

int main()
{
	static_assert(bitset<unsigned int>{0x10}[4], "???");//00010000
    
    std::cout << "Compiled ok" << std::endl;
}