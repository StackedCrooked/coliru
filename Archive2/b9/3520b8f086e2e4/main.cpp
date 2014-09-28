#include <iostream>
#include <string>
#include <vector>

#define _expand(x) x
#define expand(x)  _expand(x)

#define stringify(x) #x
#define paste(x, y) x ## y

#define gcc_ver paste(stringify(gcc-), expand(__VERSION__))

int main()
{
    std::cout << (gcc_ver);
    return 0;
}
