#include <memory>

struct A {
    A(std::shared_ptr<int> p)  {}
};

int main(int argc, char** argv) {
    A(0); // works
    std::make_shared<A>(0); // doesn't work
    return 0;
}