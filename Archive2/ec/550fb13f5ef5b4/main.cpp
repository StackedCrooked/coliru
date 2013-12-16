#include <iostream>
#include <utility>

struct Noisy {
    Noisy() { std::cout << "Default Construct" << std::endl; }
    Noisy(const Noisy& other) { std::cout << "Copy Construct" << std::endl; }
    Noisy(Noisy&& other) { std::cout << "Move Construct" << std::endl; }
    ~Noisy() { std::cout << "Destruct" << std::endl; }
    Noisy& operator= (const Noisy) & { std::cout << "Copy Assign" << std::endl; return *this; }
    Noisy& operator= (Noisy&&) & { std::cout << "Move Assign" << std::endl; return *this; }
};

Noisy getNoisy() {
    return Noisy{};
}

int main(int argc, char** argv) {
    std::cout << "---------------------------" << std::endl;
    std::cout << argv[1] << " optimizations:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    
    Noisy n = getNoisy(); // Test how many copies is being made.
    
    std::cout << "---------------------------" << std::endl;
}
