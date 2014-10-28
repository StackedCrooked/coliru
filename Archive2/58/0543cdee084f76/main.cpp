#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <type_traits>

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

template<typename InputIt,
    typename Value = typename std::iterator_traits<InputIt>::value_type>
std::vector<uint8_t> decodeHexToVector(InputIt st, InputIt en, size_t sizehint = 0)
{
    std::vector<uint8_t> bytes;
    if (sizehint)
        bytes.reserve(sizehint);
    if (!decodeHex(st, en, std::back_inserter(bytes)))
        throw std::exception();//"bad decode";
    return bytes;
}

std::vector<uint8_t> decodeHexToVector(std::string const& str)
{
    return decodeHexToVector(str.begin(), str.end(), str.length());
}

int main()
{
    char const* rawMemory = "FF3F643F";
    
    auto result = decodeHexToVector(rawMemory, rawMemory + 8);
    
    auto printResult = [&]()
    {
        for (auto& i : result)
            std::cout << (int)i << std::endl;
        std::cout << "-------------" << std::endl;
    };
    
    result = decodeHexToVector("FF3F643F");
    printResult();
        
    // wide characters
    wchar_t const* wideMemory = L"80FF11";
    result = decodeHexToVector(wideMemory, wideMemory + 6);
    printResult();
}
