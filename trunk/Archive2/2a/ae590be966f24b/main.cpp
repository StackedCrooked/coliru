#include <iostream>
#include <memory>
#include <vector>

void logSDLError(std::ostream&, std::string){}

int main() {
    logSDLError(std::cout, "something");
}