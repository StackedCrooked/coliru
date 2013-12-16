#include <array>
#include <iostream>

int main(int argc, char* argv[]) {
    constexpr std::string s{"Hello, world!"};
    std::array<char, s.size()> a;
    std::copy(s.begin(), s.end(), a.begin());
    return 0;
}