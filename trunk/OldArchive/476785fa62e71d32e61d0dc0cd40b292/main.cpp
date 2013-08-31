#include <iostream>

template <typename Tag, int = 0>
class Fruit {
    int p;
public:
    Fruit(int p) : p(p) { }
    int price() const { return p; }
};

template <typename T>
class Fruit<T, 0> : public Fruit<void, 1> {
public:
    Fruit(int p) : Fruit<void, 1>(p) { }
};

using Apple = Fruit<struct AppleTag>;
using Banana = Fruit<struct BananaTag>;

int main() {
    Apple a(12);
    Banana b(24);
    std::cout << a.price() << "\n";
}
