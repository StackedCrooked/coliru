#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <limits>
#include <cstddef>

int main()
{
    // UTF-8 data. The character U+1d10b, musical sign segno, does not fit in UCS2
    std::string utf8 = u8"z\u6c34\U0001d10b";
 
    // the UTF-8 / UTF-16 standard conversion facet
    // the UTF-8 / UCS2 standard conversion facet
    std::mbstate_t mb {};
    std::codecvt_utf8<char32_t> cvt;
    char* beg =  &*utf8.begin();
    char* end =  &*utf8.end();
    size_t length = cvt.length(mb, beg, end, std::numeric_limits<size_t>::max());
    std::cout << "Valid bytes in this UTF8 string: " << length << std::endl;
    for (int count = 0; beg < end; ++count, beg += length)
    {
        length = cvt.length(mb, beg, end, 1);
        std::cout << "A UTF-8 chracter number " << count << " of  " << length << " bytes" << std::endl;
    }
    
    beg =  &*utf8.begin();
    std::codecvt_utf8_utf16<char16_t> u8_16;
    length = u8_16.length(mb, beg, end, std::numeric_limits<size_t>::max());
    std::cout << "Can convert " << length << " bytes to UTF16" << std::endl;
    
    std::codecvt_utf8<char16_t> u8_ucs2;
    length = u8_ucs2.length(mb, beg, end, std::numeric_limits<size_t>::max());
    std::cout << "Can convert " << length << " bytes to UCS2" << std::endl;
    
}