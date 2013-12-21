#include <iostream>

int main()
{
    std::cout << "\\\\aBCDEF"  << '\n' ; // C-style literal for regex \\aBCDEF
    // each backslash needs to be escaped, we need two of them for the regex
    // two \\ for the first escaped backslash, two \\ for the second escaped backslash
    // adding up to four. "\\\\" is the C-style literal for two backslashes in succession

    // in C++, we should prefer a raw string literal for constructs of this kind
    // http://www.stroustrup.com/C++11FAQ.html#raw-strings
    std::cout << R"(\\aBCDEF)" << '\n' ; // C++ raw string literal for regex \\aBCDEF
}
