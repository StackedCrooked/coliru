#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template<typename InputIt,
    typename Ch = typename std::iterator_traits<InputIt>::value_type,
    typename OutputIt,
    typename OutType = uint8_t>
bool decodeHex(InputIt st, InputIt en, OutputIt byteOutput)
{
    std::vector<uint8_t> result;
    
    int hi = 1;
    for ( ; st != en; (hi = !hi), ++st) {
        OutType nibbles;
        Ch digit = *st;
        if (hi) nibbles = 0;
        if (digit >= '0' && digit <= '9') nibbles |= (digit - '0') << (4*hi);
        else if (digit >= 'A' && digit <= 'F') nibbles |= (digit - 'A' + 10) << (4*hi);
        else if (digit >= 'a' && digit <= 'f') nibbles |= (digit - 'a' + 10) << (4*hi);
        if (!hi)
            *byteOutput++ = nibbles;
    }
    
    // "hex ends in the middle of a byte" ?
    if (!hi)
        return false;
        
    // Success
    return true;
}

std::vector<uint8_t> decodeHexToVector(std::string const& container)
{
    std::vector<uint8_t> bytes;
    bytes.reserve(container.length() >> 1);
    if (!decodeHex(container.begin(), container.end(), std::back_inserter(bytes)))
        throw std::exception();//"bad decode";
    return bytes;
}

int main()
{
    auto result = decodeHexToVector("FF3F643F");
    for (auto& i : result)
        std::cout << (int)i << std::endl;
}
