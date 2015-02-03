#include <iostream>

std::ostream& ねこ？(std::ostream& os) {
    return os << u8"ねこです〜\n";
}

int main() {
    auto& です = std::cout;
    ねこ？(です);
}