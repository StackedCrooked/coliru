#include <iostream>

class Y {
public:
    Y() = default;
    ~Y() {
        std::cout << "Oh hai";
    }
};

class X {
public:
    X() = default;
    ~X() {
        throw std::bad_array_new_length();
    }
};

int main() 
try {
    const Y & y = Y();
    const X & x = X();
    return -2;
}
catch (std::bad_array_new_length& t) {
    return -1;
}
