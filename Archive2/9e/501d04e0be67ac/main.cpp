#include <iostream>
#include <memory>

class Red;
class Green;
class Blue;

class Color {
    friend class Red;
    friend class Green;
    friend class Blue;
    
public:
    
    static const Red* RED;
    static const Green* GREEN;
    static const Blue* BLUE;

    virtual std::string name() const = 0;
    
private:

    // prohibit instantiation of non-friend subclasses
    virtual ~Color() = default;
    
    static const Red RED_;
    static const Green GREEN_;
    static const Blue BLUE_;
};

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

const Red* Color::RED = &RED_;
const Green* Color::GREEN = &GREEN_;
const Blue* Color::BLUE = &BLUE_;

int main() {
    const Color* c = Color::GREEN;
    c = Color::BLUE;
    if (c == Color::GREEN) {
        std::cout << c-> name() << " is green" << std::endl;
    } else {
        std::cout << c-> name() << " is not green" << std::endl;
    }
    return 0;
}