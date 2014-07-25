#include <iostream>
#include <clocale>
#include <cstdio>
 
int main()
{
    int i, j;
    float x, y;
    char str1[10], str2[4];
    wchar_t warr[2];
 
    char input[] = u8"25 54.32E-1 Thompson 56789 0123 56ß水";
 
    // parse as follows:
    // an integer, a floating-point value, a word,
    // two-digit integer (digits 5 and 6)
    // a floating-point value (digits 7, 8, 9)
    // an integer which isn't stored anywhere
    // a string of integers (digits 5 and 6)
    // two wide characters, using multibyte to wide conversion
 
    std::setlocale(LC_ALL, "en_US.utf8");
    int ret = std::sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc",
                     &i, &x, str1, &j, &y, str2, warr);
 
    std::cout << "Converted " << ret << " fields:\n"
              << "i = " << i << "\nx = " << x << '\n'
              << "str1 = " << str1 << "\nj = " << j << '\n'
              << "y = " << y << "\nstr2 = " << str2 << '\n'
              << std::hex << "warr[0] = U+" << warr[0]
              << " warr[1] = U+" << warr[1] << '\n';
}