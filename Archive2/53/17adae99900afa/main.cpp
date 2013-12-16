
extern "C" char *gets(char *); // clang needs this to work....

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <iterator>

// In a header file far, far away
#include <boost/strong_typedef.hpp>
namespace stdtypes 
{
    BOOST_STRONG_TYPEDEF(uint8_t, uint8)
	inline void swap(uint8& a, uint8 &b) noexcept
	{
		decltype(auto) t = a;
		a = b;
		b = t;
	}
}

class RC4
{
	using u8 = stdtypes::uint8;
	u8 S_[256];
	u8 i_;
	u8 j_;
public:
	RC4() : i_{0}, j_{0} 
	{
		for(auto i = 0; i < 256; ++i)
			S_[i] = i;
	}

	auto operator()()
	{
		using std::swap;
		i_ += 1;
		j_ += S_[i_];
		swap(S_[i_], S_[j_]);
		return +S_[255&(S_[i_] + S_[j_])];
	}

};

int main()
{
	RC4 rc4;
	for(auto i = 0; i < 1 << 15; ++i)
		printf("%02X%s", rc4(), 63 == i % 64 ? "\n" : "");
	printf("\n");
	return 0;
}

