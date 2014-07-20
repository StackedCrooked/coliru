#include <iostream>

#define MACRO_TEXT "macro-text"

int main()
{
    void *ptr = static_cast<char*>(MACRO_TEXT);
    std::cout << ptr << std::endl;
    return 0;
}
