#include <string>
#include <array>
#include <iostream>

std::string ResultsToHex(unsigned EncodeResults) {
    const char* lut = "0123456789ABCDEF";
    std::string results;
    do {
        results.insert(0, 1, lut[EncodeResults%16]);
    } while(EncodeResults/=16);
    return results;
}

std::array<char, 256> make_lut() {
    std::array<char, 256> lut = {};
    for(int i=0; i<10; ++i)
        lut[i+'0'] = i;
    for(int i=0; i<6; ++i) {
        lut[i+'A'] = i+10;
        lut[i+'a'] = i+10;
    }
    return lut;        
}

unsigned int ResultsUnhex(const char* tBuf) {
    static const std::array<char, 256> lut = make_lut();
    unsigned results=0;
    do {
        results = results*16 + lut[*tBuf];
        ++tBuf;
    }while(*tBuf);
    return results;
}

int main() { 
    std::cout << ResultsToHex( 123456789 ) << '\n';
    std::cout << ResultsUnhex("75BCD15") << '\n';
}
