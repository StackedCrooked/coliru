#include <iostream>
#include <random>
 
int main() {
    std::random_device rd("/etc/passwd");
    std::cout << rd() << '\n';
}