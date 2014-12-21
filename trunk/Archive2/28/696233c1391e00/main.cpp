#include <stdint.h>
#include <assert.h>

#include <codecvt>
#include <cstdio>
#include <string>
#include <iostream>

std::string toSuperscript(uint32_t x)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert16;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert32;
    char buf[16];
    std::string r;
    auto digits = std::snprintf(buf, 16, "%d", x);
    assert(digits >= 0);
    r.reserve(2*digits);
    for (uint32_t i = 0; i < digits; ++i)
    {
        auto c = buf[i];
        switch (c)
        {
            case '+': r.append(convert16.to_bytes(u"⁺")); break;
            case '-': r.append(convert16.to_bytes(u"⁻")); break;
            case '0': r.append(convert16.to_bytes(u"⁰")); break;
            case '1': r.append(convert16.to_bytes(u"¹")); break;
            case '2': r.append(convert16.to_bytes(u"²")); break;
            case '3': r.append(convert16.to_bytes(u"³")); break;
            default:
            {
                assert(c >= '4' && c <= '9');
                uint32_t offset = c-'4';
                r.append(convert32.to_bytes(U'⁴' + offset));
                break;
            }
        }
    }
    return r;
}

int main()
{
    std::cout << u8"ℯ" << toSuperscript(1234567890) << std::endl;
    std::cout <<  u8"ℯ" << toSuperscript(-1234567890) << std::endl;
    return 0;
}