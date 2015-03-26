#include <iostream>
#include <memory>
#include <vector>

struct Ball {
    virtual void hi() {
        std::cout << "I'm just a plain ball\n";
    }
};

struct BouncyBall : Ball {
    void hi() {
        std::cout << "I'm a bouncy ball\n";
    }
};

using std::make_unique;

int main() {
    std::vector<std::unique_ptr<Ball>> ballz;
    ballz.push_back(make_unique<Ball>());
    ballz.push_back(make_unique<BouncyBall>());
    for (auto const & b : ballz) {
        b->hi();
    }
}
