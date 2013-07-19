#include <iostream>
#include <string>

struct Colour {
    enum ColourType {
        RED, BLUE, GREEN
    };
    static std::string to_string(ColourType colour) {
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
};

int main() {
    auto colour = Colour::RED;
    std::cout << Colour::to_string(colour);
}