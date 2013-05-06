#include <iostream>
#include <cstdint>

typedef unsigned __int128 uint128_t;


constexpr bool is_hex(const char *s)
{
    return s[0] == '0' && (s[1] == 'x' || s[1] == 'X');
}

constexpr bool is_dec(const char *s)
{
	return s[0] >= '1' && s[0] <= '9';
}

constexpr bool is_oct(const char *s)
{
	return s[0] == '0';
}

constexpr uint8_t from_hex(const char c)
{
	return (c >= '0' && c <= '9') ? c - '0' : 
	       (c >= 'A' && c <= 'F') ? c - 'A' + 10 : 
	       (c >= 'a' && c <= 'f') ? c - 'a' + 10 : 
	       throw;
}

constexpr uint8_t from_dec(const char c)
{
	return (c >= '0' && c <= '9') ? c - '0' : throw;
}

constexpr uint8_t from_oct(const char c)
{
	return (c >= '0' && c <= '7') ? c - '0' : throw;	
}

constexpr uint128_t conv10(const char *s, const size_t i = 0, const uint128_t r = 0)
{
	return s[i] ? conv10(s, i + 1, r*10 + from_dec(s[i])) : r;
}

constexpr uint128_t conv16(const char *s, const size_t i = 0, const uint128_t r = 0)
{
	return s[i] ? conv16(s, i + 1, r*16 + from_hex(s[i])) : r;
}

constexpr uint128_t conv8(const char *s, const size_t i = 0, const uint128_t r = 0)
{
	return s[i] ? conv8(s, i + 1, r*8 + from_oct(s[i])) : r;
}

constexpr uint128_t operator"" _u128(const char *s)
{
	return is_hex(s) ? conv16(s + 2) : 
	       is_dec(s) ? conv10(s)     : 
	       is_oct(s) ? conv8(s + 1)      : 
	       throw;
}

std::ostream& operator<<(std::ostream& os, const uint128_t a)
{
    os << "0x" << std::hex << static_cast<uint64_t>(a >> 64);
	os         << std::hex << static_cast<uint64_t>(a >>  0);
	return os;
}


int main()
{
    constexpr uint128_t T = 170141183460469231731687303715884105727_u128;
	constexpr uint128_t U = 0x7fffffffffffffffffffffffffffffff_u128;
	std::cout << T << std::endl;
	std::cout << U << std::endl;
    return 0;
}