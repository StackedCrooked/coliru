#include <iostream>

class Noisy {
    int x;
public:
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
    
    friend void swap (Noisy & lhs, Noisy & rhs); 
};

void swap (Noisy & lhs, Noisy & rhs) {
    std::swap(lhs.x, rhs.x);
}

class Test {
    Noisy n;
public:
    Noisy foo() & {
        std::cout << "foo() &\n";
        Noisy temp;
        swap(temp, n);
        return std::move(temp);
    }
    
    Noisy foo() && {
        std::cout << "foo() &&\n";
        return std::move(n);
    }
};

int main() {
    Test t;
    Noisy n = t.foo();
    
    Noisy n2 = Test().foo();
}