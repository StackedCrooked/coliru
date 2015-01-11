#include <utility>

int main() {
    std::pair<char, int> pair = std::make_pair('a', 42);
    std::pair<const double, bool> converted = pair;

    return converted.second ? converted.first / 3 : -converted.first;
}
