#include <iostream>
#include <string>
#define TESTING
#define PRINT(x) #x
#define SHOW(x) PRINT(x)

int main() {
    std::cout << std::string { SHOW(TESTING) }.size() << '\n';
}