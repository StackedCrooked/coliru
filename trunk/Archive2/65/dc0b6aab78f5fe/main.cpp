#include <sstream>

int main() {
    std::stringstream ss("100000000000000000000000");
    ss.exceptions(std::ios::failbit); // throws on all tested implementations
    
    int i;
    ss >> i;

}
