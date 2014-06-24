#include <iostream>

struct Logger {
    void log(const char*) {}
};

struct MyClass {
    void myFunction();
    Logger myMember;
};

template <typename T, typename U, typename F>
void connect(T&&, U&&, F f) {
    f();
}

template <typename F>
void sendCommand(F f) {
    f();
}

int action, trigger;

void MyClass::myFunction() {
    std::cout << this << std::endl;
    // call the lambda1
    connect(action, trigger, [this]() {
        std::cout << this << std::endl;
        // in the lambda1, call lambda2
        sendCommand([this]() {      // <-- I want `this` point to the outter class
            std::cout << this << std::endl;
            this->myMember.log("something");  // myMember is the member of class MyClass
        });
    });
}

int main() {
    MyClass o;
    o.myFunction();
}
