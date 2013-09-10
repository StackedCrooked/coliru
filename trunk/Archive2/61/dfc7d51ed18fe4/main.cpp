#include <utility>
#include <iostream>

struct MoveOnly
{
    MoveOnly() = default;
    MoveOnly(MoveOnly&&) {std::cout << "MoveOnly moved" << std::endl;};
};

struct ContainsMoveOnly
{
    MoveOnly mo;
};

int main() {
    auto mo  = MoveOnly();    // probably constructed in place -> silent
    auto mo2 = std::move(mo); // MoveOnly moved

    auto cmo  = ContainsMoveOnly(); // probably constructed in place -> silent
    auto cmo2 = std::move(cmo);     // MoveOnly moved

    return 0;
}
