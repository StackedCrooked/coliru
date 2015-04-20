#include <string>
#include <sstream>
#include <iomanip>

#include <cstdint>
#include <iostream>
#include <bitset>

std::string pp(const uint32_t IN)
{
    std::stringstream ss;
	ss << ((IN >> 24) & 0xF);   // major
	ss << '.';
	ss << ((IN >> 16) & 0xF);   // minor
	ss << '.';
    ss << std::setw(2) << std::setfill('0');
	ss << ((IN >> 00) & 0xFF);  // patch
	
	return ss.str();
}

int main()
{
    // SyncBOX encoded reg 0x01000001
    std::cout << pp(std::bitset<32>("0000" "0011" "0000" "0010" "0000" "0000" "0000" "0001").to_ulong()) << '\n';
}
