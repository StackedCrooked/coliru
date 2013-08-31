#include <iostream>
#include <string>

using namespace std;


int main() {
    int max = 42;
    std::string mess("ERROR: THE MAX IS: ");
    mess += std::to_string(max);
    std::cout << mess;
}