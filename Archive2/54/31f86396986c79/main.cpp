#include <iostream>
#include <stdexcept>

void log_error() {
    try {
        std::rethrow_exception(std::current_exception());
    }
    catch(const std::runtime_error& ex) {
        std::cout << "runtime_error: " << ex.what() << std::endl;
    }
    catch(...) {
    }
}


int main() {
    try {
        throw std::runtime_error("blah");
    }
    catch(...) {
        log_error();
    }
}
