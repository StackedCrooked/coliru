#include <vector>
#include <iostream>
 
struct Noisy {
    Noisy() {std::cout << "constructed\n"; }
    Noisy(const Noisy&) { std::cout << "copied\n"; }
    Noisy(Noisy&&) { std::cout << "moved\n"; }
    ~Noisy() {std::cout << "destructed\n"; }
};
 
void fn_by_val(Noisy unused_n) {
    std::cout << "Fn called\n";
}
 
int main()
{
   Noisy n;
   fn_by_val(std::move(n));
}