#include <iostream>
#include <sstream>
#include <cstdio>

int main() {
    std::stringstream ret;
    ret << "Result is " << 100 << "% successful hits\n";
    std::cout << ret.str();
    std::printf(ret.str().c_str(), "<exposing bug>");
    return 0;
}
