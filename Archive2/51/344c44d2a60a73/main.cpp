#include <thread>

class Base {
public:
    void foo(); // a forever loop which could be interruptted
};

class Derived_1 : public Base {
    // ...
};

class Derived_2 : public Base {
    // ...
};

void Base::foo() {
}

int main() {
    Derived_1 d1;
    Derived_2 d2;
    std::thread t1(&Base::foo, &d1);
    std::thread t2(&Base::foo, &d2);

    t1.join();
    t2.join(); // seg fault, gdb said it's a corrupt stack
    return 0;
}
