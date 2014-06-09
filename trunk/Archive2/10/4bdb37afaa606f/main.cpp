#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> v{{"Hello", "there"}};
    std::cout << v.size() << ' ' << v[0];
}