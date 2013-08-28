#include <exception>
#include <iostream>

int main() {
    std::set_terminate([] {
        try {
            throw;
        } catch(int) {
            std::cout << "there it is!";
        }
    });
    
    throw 42;
}