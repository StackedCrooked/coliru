#include <iostream>
#include <cstdio>
#include <stdarg.h>
using namespace std;

struct A {
    void operator() (const char * sFormat, ...) {
        va_list args;
        va_start(args, sFormat);
        // std::string res = format(formatStr, args);
        vprintf(sFormat, args);
        va_end(args);
    };
};

int main()
{
//    auto displayMessage = [] (const char * sFormat, ...) {
//        va_list args;
//        va_start(args, sFormat);
//        // std::string res = format(formatStr, args);
//        vprintf(sFormat, args);
//        va_end(args);
//    };
//    
//    displayMessage("%d - %d - %d\n", 1, 2, 3);
   
    A a;
    a("%d - %d - %d\n", 1, 2, 3);
}
