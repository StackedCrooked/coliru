#include <iconv.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

std::wstring atow(const std::string& utf8) {
    std::wstring result(utf8.length()*2, '\0'); //*2 isn't always big enough
    iconv_t conv = iconv_open("UTF-32", "UTF-8");
    char* source = (char*)&utf8[0];
    size_t  sourcebytesleft = utf8.size();
    char* destination = (char*)&result[0];
    size_t destbytesleft = result.size()*sizeof(wchar_t);
    std::cerr << source << ' ' << sourcebytesleft << ' ' << destination << ' ' << destbytesleft << '\n';
    int err = iconv(conv, &source, &sourcebytesleft, &destination, &destbytesleft);
    std::cerr << err << ' ' << source << ' ' << sourcebytesleft << ' ' << destination << ' ' << destbytesleft << '\n';
    iconv_close(conv);
    if (err == -1) {
        switch (errno) {
        case EILSEQ: throw std::runtime_error("Input conversion stopped due to an input byte that does not belong to the input codeset."); 
        case E2BIG: throw std::runtime_error("Input conversion stopped due to lack of space in the output buffer."); 
        case EINVAL: throw std::runtime_error("Input conversion stopped due to an incomplete character or shift sequence at the end of the input buffer."); 
        case EBADF: throw std::runtime_error("The cd argument is not a valid open conversion descriptor."); 
        default: throw std::runtime_error("Unknown error returned from iconv"); 
        }
    }
    std::cerr << result.size() << ' ' << destbytesleft << '\n';
    result.resize(result.size()-destbytesleft/sizeof(wchar_t));
    return result;
}

int main() {
    //codepoint U+24B62 𤭢
    // UTF8  F0A4ADA2
    // UTF16 D852DF62
    // UTF32 24B62
    std::string utf8 = "\xF0\xA4\xAD\xA2";
    std::cerr << std::hex;
    std::cerr << utf8.size() << ' ' << +utf8[0] << ' ' << +utf8[1] << ' ' << +utf8[2] << ' ' << +utf8[3] << '\n';
    std::wstring utf16 = atow(utf8);
    std::cerr << utf16.size() << ' ' << +utf16[0] << ' ' << +utf16[1];
    
}