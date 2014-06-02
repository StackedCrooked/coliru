#include <iostream>
 
struct Noisy {
    Noisy() {std::cout << "constructed\n"; }
    Noisy(const Noisy&) { std::cout << "copied\n"; }
    Noisy(Noisy&&) { std::cout << "moved\n"; }
    ~Noisy() {std::cout << "destructed\n"; }
};
 
 Noisy N(){return std::move(Noisy());}
 Noisy N2(){return Noisy();}
 
int main()
{
    Noisy n = N();
    // Noisy N2();
}