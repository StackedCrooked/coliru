#include <string>

enum class Colour {
    RED, BLUE, GREEN
};

std::string colour_to_string(Colour colour) {
    switch(colour) {
        case Colour::RED:
            return std::string("RED");
        case Colour::BLUE:
            return std::string("BLUE");
        case Colour::GREEN:
            return std::string("GREEN");
        default:
            return std::string("");
    }
}

#include <iostream>

int main() {
    Colour red = Colour::RED;
    std::cout << colour_to_string(red);
}