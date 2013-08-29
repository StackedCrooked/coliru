#include <iostream>

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

#define STRINGIFIED_PREPROCESSOR_VARIABLES __DATE__ " " __TIME__ " " __FILE__ " " STRINGIFY(__LINE__)

int main() {
    std::cout << STRINGIFIED_PREPROCESSOR_VARIABLES << std::endl;
    const char * test = STRINGIFIED_PREPROCESSOR_VARIABLES;
    std::cout << test << std::endl;
}