#include <iostream>
#include <stdexcept>

void unexpected() /*DEPRECATED*/ {
    try {
        throw; // rethrow the current exception
    } catch (int n) {
        std::cout << "UNEXPECTED: int. Recover by rethrowing a bool." << std::endl;
        throw bool(n);
    } catch (const std::exception & exc) {
        std::cout << "UNEXPECTED: " << exc.what() << ". No recovery is possible." << std::endl;
    }
}

void may_throw_bool() throw(bool) /*DEPRECATED*/{
     // 'unexpected' is called. there we can recover by rethrowing as bool.
    throw int();
} 

void must_not_throw() throw() /*DEPRECATED*/ {
    // 'unexpected' is called, followed by terminate. no recovery is possible.
    throw std::runtime_error("foo_exception");
} 

void must_not_throw_cpp11() noexcept {
    // terminate is called immediately ('unexpected' is not called)
    throw std::runtime_error("foo_exception"); // oops, not allowed, terminate!
}

int main() {
    // register the unexpected handler
    std::set_unexpected(&unexpected); /*DEPRECATED*/
    
    try {
        may_throw_bool();
    } catch (bool b) {
        std::cout << "Caught bool: " << b << std::endl;
    }
    
    try {
        must_not_throw();
    } catch (...) {
        std::cout << "unreachable" << std::endl;
    }
    
    try {
        must_not_throw_cpp11();
    } catch (...) {
        std::cout << "unreachable" << std::endl;
    }
}