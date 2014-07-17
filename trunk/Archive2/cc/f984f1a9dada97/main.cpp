#include <iostream>

int main() {
    auto fn = [](auto arg) {
        std::cout << arg << '\n';
    };
    fn("Fuck off faggot!");
    fn(2 + 2);
    fn("Holy shit!");
}
