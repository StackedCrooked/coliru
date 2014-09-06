#include <memory>

struct Cat;

struct Dog {
    Dog();
    std::unique_ptr<Cat> cat;
};

struct Cat {
    Dog dog;
};

Dog::Dog(): cat(new Cat) { }

int main() {
    Cat cat;
}
