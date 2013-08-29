int main() {}

#include <array>

static_assert(sizeof(std::array<char, 3>) == 3, "No padding here");
