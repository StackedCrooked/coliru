#include <iostream>

class Noisy {
    int x;
    
    Noisy() {
        std::cout << "Noisy()\n";
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

class Test {
    Noisy n;
    
    Noisy foo() {
        Noisy temp;
        std::swap(temp, n);
        return std::move(temp);
    }
    
    Noisy foo() && {
        std::cout << "foo() &&\n";
        return std::move(n);
    }
};

int main() {
    const char* const c = "abc";
    c = "def";
}