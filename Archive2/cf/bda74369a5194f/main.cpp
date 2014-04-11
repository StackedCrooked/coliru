#include <iostream>

class color {
public:
    enum internal_color { red, green, blue };
    color(internal_color c_): c(c_) {}
    operator internal_color() { return c; }
    color opposite() { return color(internal_color(blue - c)); }
    static bool invalid_color(int i) { return i < red || i > blue; }
    static color validated_color(int i) { if( invalid_color(i) ) throw "blblb"; return color(internal_color(i)); }
private:
    internal_color c;
};

int main() {
    color c(color::red);
    std::cout << c << std::endl;
    auto d = color::validated_color(1);
    std::cout << d << std::endl;
    auto x = c.opposite();
    std::cout << x << std::endl;
    auto e = color::invalid_color(3);
    std::cout << e << std::endl;
/*
    color f(5); // does not compile in c++11
    std::cout << f << std::endl;
*/
}    

