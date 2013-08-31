#include <iostream>
#include <string>

int main() {
    std::string orig = "Hello World!\n";
    std::string copy;
    std::copy(orig.begin(), orig.end(), copy.begin());
    std::cout << copy;
    return 0;
}