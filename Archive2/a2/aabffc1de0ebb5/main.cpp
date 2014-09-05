#include <iostream>
#include <memory>
#include <vector>

class Red;
class Green;
class Blue;

class Color {
    friend class Red;
    friend class Green;
    friend class Blue;
    
public:
    
    static const Color* RED;
    static const Color* GREEN;
    static const Color* BLUE;

    virtual std::string name() const = 0;
    
private:

    // prohibit instantiation of non-friend subclasses
    virtual ~Color() = default;
    
    static const Red RED_;
    static const Green GREEN_;
    static const Blue BLUE_;
};

typedef const Color* Color_t;

class Red : public Color {
    friend class Color;
private:
    Red() {};  // prohibit instantiation other than by Color
    std::string name() const {return "Red";}
};

class Green : public Color {
    friend class Color;
private:
    Green() {};
    std::string name() const {return "Green";}
};

class Blue : public Color {
    friend class Color;
private:
    Blue() {};
    std::string name() const {return "Blue";}
};

const Red Color::RED_;
const Green Color::GREEN_;
const Blue Color::BLUE_;

const Color* Color::RED = &RED_;
const Color* Color::GREEN = &GREEN_;
const Color* Color::BLUE = &BLUE_;

int main() {
    Color_t c = Color::GREEN;
    c = Color::BLUE;
    if (c == Color::GREEN) {
        std::cout << c-> name() << " is green" << std::endl;
    } else {
        std::cout << c-> name() << " is not green" << std::endl;
    }
    
    // we can make collections of colors easily
    std::vector<Color_t> colors = { Color::RED, Color::RED, Color::GREEN, Color::BLUE, Color::GREEN };
    return 0;
}