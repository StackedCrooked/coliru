#include <iostream>
#include <stdexcept>
#include <cstring>

//invlaid code points and such
struct invalid_unicode : std::runtime_error {
    invalid_unicode(std::string msg) :std::runtime_error(std::move(msg)) {}
};
//invalid encoding.
struct invalid_utf8 : std::runtime_error {
    invalid_utf8(std::string msg) :std::runtime_error(std::move(msg)) {}
};


bool is_utf8_cont(char c)
{
    return c&0x80 && !(c&0x40);
}
unsigned extract_ucode_utf8(const char*& o) {
    
    const unsigned char* s = reinterpret_cast<const unsigned char*>(o);
    if (s[0]<0x80) {
        ++o; 
        unsigned lo = s[0]&0x7F;
        unsigned r = lo;
        return r;
    }
    if (s[0]<0xC0) 
        throw invalid_utf8("invalid lead byte: "+std::to_string(s[0]));
    if (s[0]<0xE0) {
        if (is_utf8_cont(s[1]) == false)
            throw invalid_utf8("invalid continuation byte: "+std::to_string(s[1]));
        o += 2;
        unsigned hi = s[0]&0x1F;
        unsigned lo = s[1]&0x3F;
        unsigned r = (hi<<6) | lo;
        return r;
    }
    if (s[0]<0xF0) {
        if (is_utf8_cont(s[1]) == false)
            throw invalid_utf8("invalid continuation byte: "+std::to_string(s[1]));
        if (is_utf8_cont(s[2]) == false)
            throw invalid_utf8("invalid continuation byte: "+std::to_string(s[2]));
        o += 3;
        unsigned hi = s[0]&0x1F;
        unsigned mid = s[1]&0x3F;
        unsigned lo = s[2]&0x3F;
        unsigned r = (hi<<12) | (mid<<6) | lo;
        return r;
    }
    throw invalid_utf8("invalid lead byte: "+std::to_string(s[0]));
}

int main (int, char *[])
{
  const char src[13] = u8"Б№1АГД"; //string which contains cyrillic symbols
  const char* s = src;

  while (*s) {
    int ucode = extract_ucode_utf8(s);
    printf ("ucode = 0x%x\n", ucode);
  }
}