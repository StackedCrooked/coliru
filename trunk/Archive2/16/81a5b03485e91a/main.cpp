#include <string>
#include <cassert>

template <typename Out>
void hex2bin(std::string const& s, Out out) {
    assert(s.length() % 2 == 0);

    std::string extract;
    for (std::string::const_iterator pos = s.begin(); pos<s.end(); pos += 2)
    {
        extract.assign(pos, pos+2);
        *out++ = std::stoi(extract, nullptr, 16);
    }
}

#include <iostream>
#include <vector>

int main()
{
    std::vector<unsigned char> v;

    hex2bin("1023456789ABCD", back_inserter(v));

    for (auto byte : v)
        std::cout << std::hex << (int) byte << "\n";
}
