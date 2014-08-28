#include <stdexcept>
#include <iostream>

void rethrow() {
    try {
        throw;
    } catch (std::runtime_error& e) {
        std::cout << "runtime_error: " << e.what() << "\n";;
    } catch (...) {
        std::cout << "unknown exception\n";
    }
}

int main()
{
    try {
        throw std::runtime_error("testing...");
    } catch (...) {
        rethrow();
    }
}
