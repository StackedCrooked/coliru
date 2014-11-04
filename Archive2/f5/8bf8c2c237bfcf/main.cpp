#include <iostream>

// Here be threadsafity dragons.
int counter = 0;

// (And all other kinds of bugs (cv?), proof of concept.)
template<class T>
int type_id(const T&) {
    static int id = counter++;
    return id;
}

int main(int argc, char** argv) {
    std::cout << type_id(0) << "\n";
    std::cout << type_id("test") << "\n";
    std::cout << type_id(0) << "\n";
    std::cout << type_id("test") << "\n";
    std::cout << type_id("test") << "\n";
    std::cout << type_id(0) << "\n";
    std::cout << type_id(0) << "\n";
    return 0;
}