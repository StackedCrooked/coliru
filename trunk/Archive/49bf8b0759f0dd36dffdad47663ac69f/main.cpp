#include <algorithm>
#include <string>
#include <cctype>
#include <climits>
#include <iostream>
#include <cassert>

// the issue crops up when char is a signed type
static_assert(std::is_signed<char>::value,
              "the is a system where char is signed");

// isspace takes an int;
// it has undefined behaviour when that int value
// is beyond the range of unsigned char (C99 §7.4/1)

// let us write a function to do
// some validation before calling isspace
int my_isspace(int c) {
    // assert that c is in the range of unsigned char [0, UCHAR_MAX]
    assert(c <= int(UCHAR_MAX) && c >= 0);
    // call isspace normally
    return ::isspace(c);
}

int main()
{
    // in a two's complement system, 0xA1 as a char is -95 
    static_assert(char(0xA1) == -95,
                  "this is a system where 0xA1 as a char is -95");

    // a string with a char with the eighth bit size set
    // (it does not really matter which one, as long as the MSB is set)
    // (in this case, I picked 0xA1 which is the inverted exclamation mark in latin-1)
    std::string s = "a\xA1g";

    // do the erasure
    s.erase( std::remove_if( s.begin(), s.end(), ::my_isspace ), s.end() );

    // if an assertion triggered, it means that isspace was called with
    // undefined behaviour; it does not have to return true or false:
    // as an example, it can segfault (imagine it uses a lookup table for only the 7-bit values).
}