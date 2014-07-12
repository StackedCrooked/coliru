#include <iostream>
#include <string>

int main() {
    std::string addressString{"BEEF"};
    addressString.insert(0, (12-addressString.size()), '0');
    std::cout << addressString << '\n';
}
