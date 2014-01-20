#include <iostream>
#include <fstream>
#include <iterator>
int main()
{
    std::basic_filebuf<char> f;
    f.open("test.txt", std::ios::out);
 
    std::ostreambuf_iterator<char_t> out1(&f);
 
    std::ostreambuf_iterator<wchar_t> out2(std::wcout);
 
    *out1 = 'a';
    *out2 = L'a';
}