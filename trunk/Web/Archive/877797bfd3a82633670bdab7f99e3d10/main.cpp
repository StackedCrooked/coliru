#include <algorithm>
#include <string>
#include <cctype>
#include <climits>
#include <iostream>
#include <cassert>

bool my_isspace(int c) {
    assert(c <= UINT_MAX && c >= 0);
    return ::isspace(c);
}

int main()
{
    std::string s = "a\xA1g";
    s.erase( std::remove_if( s.begin(), s.end(), ::my_isspace ), s.end() );
}