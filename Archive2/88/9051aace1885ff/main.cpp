#include <exception>
#include <iostream>
 
struct SomeException {
    int content = 42;
}; // struct SomeException
 
int main() {
    std::exception_ptr ptr;
    try {
        throw SomeException{};
    } catch (...) {
        ptr = std::current_exception();
    }
 
    try {
        std::rethrow_exception(ptr);
    } catch (SomeException& e) {
        std::cout << "First: " << e.content << "\n";
        e.content *= 2;
    }
     
    try {
        std::rethrow_exception(ptr);
    } catch (SomeException const& e) {
        std::cout << "Second: " << e.content << "\n";
    }
    return 0;
}