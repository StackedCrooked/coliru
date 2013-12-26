#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#define SUCCESS 1

#ifdef SUCCESS
    #undef SUCCESS
    #define SUCCESS  0
#endif //SUCCESS

int main(int argc, char *argv[]) {
    std::cout << SUCCESS;
    return 0;
}