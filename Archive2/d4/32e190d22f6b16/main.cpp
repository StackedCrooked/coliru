#include <iostream>
#include <vector>
using namespace std;

class Movable {
private:
    std::string name;
public:
    Movable() {}

    Movable(const Movable& other) {
        name = other.name;
        std::cout << "Copy constructor Movable" << std::endl;
    }

    Movable(Movable&& other) TEST {
        std::cout << "Move constructor Movable" << std::endl;
        name = std::move(other.name);
    }
};

int main() {
    std::vector<Movable> vec;
    Movable moved;
    for (int i = 0; i < 10; i++)
        vec.push_back(moved);
}