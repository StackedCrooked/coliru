#include <memory>

struct A {
    A(std::shared_ptr<int> p)  {}
};


int main() {
    A a(int(0)); // works
    //std::make_shared<A>(0); // doesn't work
}