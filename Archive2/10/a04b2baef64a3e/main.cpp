#include <iostream>
#include <string>

enum class Rotation { CW = 1, CCW = -1 };

std::ostream& operator<<(std::ostream& out, Rotation r) {
    return out << (r == Rotation::CW ? "clockwise" : r == Rotation::CCW ? "counter-clockwise" : "unknown");
}

void show(Rotation r) {
    std::cout << "Rotation value " << int(r) << " is registered as " << r << '\n';
}

int main(int argc, char** argv) {
    show(Rotation::CW);
    show(Rotation::CCW);
    // show(42); // This is a type error
    // show(1);  // So is this
    show(Rotation(42));  // This is fine
    return 0;
}