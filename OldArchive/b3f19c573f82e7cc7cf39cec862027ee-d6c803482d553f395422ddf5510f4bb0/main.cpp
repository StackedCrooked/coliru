#include <iostream>

void log_and_rethrow() {
    std::cout << "logging this shit before rethrowing\n";
    throw;
}

void f() {
    try {
        throw 42;
    } catch(int) {
        log_and_rethrow();
    }
}

int main() {
    try {
        f();
    } catch(int) {
        std::cout << "caught on main";
    }
}