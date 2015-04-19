#include <iostream>
#include <vector>

struct X {
private:
    static int iglobal;
    const int i;
public:
    X() : i(++iglobal) {
        std::cout << "X(" << i << ")" << std::endl;
    }
    ~X() {
        std::cout << "~X(" << i << ")" << std::endl;
    }
};

int X::iglobal = 0;

int main() {
    std::vector<X> objects;
    for (int i = 10; i != 0; --i) {
        objects.emplace_back();
    }
    std::cout << "the end" << std::endl;
}