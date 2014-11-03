#include <iostream>
#include <string>
#include <stdlib.h>

int main() {
    std::string* s = (std::string*)calloc(1, sizeof(std::string));
    std::cout << (*s);
}
