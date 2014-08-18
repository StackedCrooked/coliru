#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>

int main()
{
    std::ifstream file { "source.utf32.txt", std::ios_base::binary };

    std::vector<char> bytes;
    std::copy(std::istreambuf_iterator<char> { file }, {}, std::back_inserter(bytes));
    assert( bytes.size() % 4 == 0 );

    std::vector<char32_t> units;
    // for want of `units = transform(strided(bytes, 4), read_one)`
    for(auto data = bytes.data(), stop = data + bytes.size(); data != stop; data += 4) {
        // aliasing through (unsigned|plain) char is fine
        auto const read = reinterpret_cast<const unsigned char*>(data);
        units.emplace_back(
                (read[3] << 24u)
                | (read[2] << 16u)
                | (read[1] << 8u)
                | (read[0] << 0u)
                );
    }
    // Get rid of BOM
    if(!units.empty() && units.front() == U'\uFEFF') units.erase(units.begin());

    // This is how I display UTF-32 on Linux
    std::locale::global(std::locale(""));
    for(auto& unit: units) {
        std::wcout << static_cast<wchar_t>(unit);
    }
}