#include <iostream>
#include <strstream>
#include <string>
 
int main()
{
    // dynamic buffer
    std::strstream s1; // dynamic buffer
    s1 << 1 << ' ' << 3.14 << " example" << std::ends;
    std::cout << "buffer holds '" << s1.str() << "'\n";
    s1.freeze(false);
 
    int n; double d;
    std::string w;
    s1 >> n >> d >> w;
    std::cout << "Read back: n = " << n
              << " d = " << d
              << " w = '" << w << "'\n";
 
    // static buffer
    char arr[20] = "-1 -3.14 ";
    std::strstream s2(arr, sizeof arr, std::ios_base::app);
    s2 << "another" << std::ends;
    std::cout << "buffer holds: '" << s2.str() << "'\n";
    s2 >> n >> d >> w;
    std::cout << "Read back: n = " << n
              << " d = " << d
              << " w = '" << w << "'\n";
}