#include <iostream>

std::ostream& ねこ？(std::ostream& os) {
    return os << u8"です\n";
}

int main() {
    auto& ねこ = std::cout;
    ねこ？(ねこ);
}