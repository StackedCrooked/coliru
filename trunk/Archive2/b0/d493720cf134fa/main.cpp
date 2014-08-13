#include <iostream>
#include <memory>
#include <vector>

class Animal {
public:
    int fullness = 50;
    virtual void eat() = 0;
};

class Lion : public Animal {
    void eat() {
        std::cout << "I'm eating meat.\n";
        fullness += 15;
    }
};

class Zebra : public Animal {
    void eat() {
        std::cout << "I'm eating grass.\n";
        fullness += 10;
    }
};

int main() {
    std::vector<std::unique_ptr<Animal>> animals;
    for (int i = 0; i < 20; ++i) {
        if (rand() % 2 == 0)
            animals.push_back(std::make_unique<Lion>());
        else
            animals.push_back(std::make_unique<Zebra>());
    }
    for (auto& a : animals) {
        a->eat();
    }
}
