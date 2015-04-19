#include <string>
#include <vector>
void main_(std::vector<std::string> const& argv);
int main(int argc, char const** argv) {
    std::vector<std::string> argv_vector(argv, argv + argc);
    main_(argv_vector);
    return 0;
}
#define main main_

// usage example
#include <iostream>
#include <string>
#include <vector>

void main(std::vector<std::string> const& argv) {
    for (auto const& arg : argv) {
        std::cout << arg << '\n';
    }
}