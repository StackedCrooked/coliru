#include <iostream>

class Noisy {
    int x;
public:
    Noisy() {
        std::cout << "Noisy()\n";
    }
    
    Noisy& operator=(Noisy &&rhs) {
        std::cout << "operator==(Noisy&&)\n";
        return *this;
    }
    
    Noisy& operator=(Noisy const& rhs) {
        std::cout << "operator==(Noisy const&)\n";
        return *this;
    }
    
    Noisy(Noisy&& rhs) {
        std::cout << "Noisy(Noisy&&)\n";
    }
    
    Noisy(Noisy const& rhs) {
        std::cout << "Noisy(Noisy const&)\n";
    }
    
    ~Noisy() {
        std::cout << "~Noisy()\n";
    }
    
};

int main() {
    Noisy n = Noisy();
}