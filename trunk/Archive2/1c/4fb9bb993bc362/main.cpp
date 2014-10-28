#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template<typename InputIt,
    typename Ch = typename std::iterator_traits<InputIt>::value_type>
std::vector<uint8_t> decodeHex(InputIt st, InputIt en)
{
    std::vector<uint8_t> result;
    int hi = 1;
    for ( ; st != en; (hi = !hi), ++st) {
        uint8_t nibbles;
        Ch digit = *st;
        if (hi) nibbles = 0;
        if (digit >= '0' && digit <= '9') nibbles |= (digit - '0') << (4*hi);
        else if (digit >= 'A' && digit <= 'F') nibbles |= (digit - 'A' + 10) << (4*hi);
        else if (digit >= 'a' && digit <= 'f') nibbles |= (digit - 'a' + 10) << (4*hi);
        if (!hi)
            result.emplace_back(nibbles);
    }
    if (st == en && !hi)
        throw std::exception();// "hex ends in the middle of a byte"
    return result;
    
}

std::vector<uint8_t> decodeHex(std::string const& container)
{
    return decodeHex(container.begin(), container.end());
}

int main()
{
    auto result = decodeHex("FF3F643F");
    for (auto& i : result)
        std::cout << (int)i << std::endl;
}
