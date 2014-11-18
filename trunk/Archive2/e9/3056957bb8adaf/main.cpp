#include <sstream>

int main() {
    std::stringstream ss("as");
    ss.exceptions(std::ios::failbit); // throws on all tested implementations
    ss.setstate(std::ios::failbit);
}
