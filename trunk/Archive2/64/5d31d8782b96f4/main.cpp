#include <memory>
#include <vector>
#include <iostream>

struct A {
    A() { std::cout << "Constructed A\n"; }
    ~A() { std::cout << "Destructed A\n"; }
};

struct B {
    B() { std::cout << "Constructed B\n"; }
    ~B() { std::cout << "Destructed B\n"; }
};

struct C {
    C() { std::cout << "Constructed C\n"; }
    ~C() { std::cout << "Destructed C\n"; }
};

struct D {
    D(int x) { std::cout << "Constructed D\n"; }
    ~D() { std::cout << "Destructed D\n"; }
};

struct ContentManager {
private:
    std::vector<std::shared_ptr<void>> data;
public:
    template<typename T, typename... Args>
    void Load(Args&&... args) {
        data.push_back(std::make_shared<T>(std::forward<Args>(args)...));
    }
};

int main() {
    ContentManager x;
    x.Load<A>();
    x.Load<B>();
    x.Load<C>();
    x.Load<D>(10);
}