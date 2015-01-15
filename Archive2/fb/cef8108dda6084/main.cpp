#include <functional>
#include <list>
#include <iostream>

typedef std::function<bool(int)> callback_t;

std::list<callback_t> callbacks;

void register_callback(callback_t callback) {
    callbacks.push_back(callback);
}

void register_callback(std::function<bool()> callback) {
    // just use a lambda with an unused int param
    // capture callback by value - capturing by reference here
    // is undefined behavior since callback is now a stack-allocated
    // local about to go out of scope
    callbacks.push_back([callback](int) {
        return callback();
    });
}

int main() {
    // explicitly pass std::functions here since gcc4.6 is
    // complaining about ambiguity with the lambdas
    register_callback(std::function<bool(int)>([](int x) {
        return x%2 == 0;
    }));

    for (int i = 0; i < 5; ++i) {
    register_callback(std::function<bool()>([]() {
        return false;
    }));
    }
    
    
    for (auto & c : callbacks) {
        std::cout << std::boolalpha << c(2) << std::endl;   
    }

    return 0;
}