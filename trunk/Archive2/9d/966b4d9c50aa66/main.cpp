#include <vector>
#include <iostream>
 
struct Noisy {
    Noisy() {std::cout << "constructed\n"; }
    Noisy(const Noisy&) { std::cout << "copied\n"; }
    Noisy(Noisy&&) { std::cout << "moved\n"; }
    ~Noisy() {std::cout << "destructed\n"; }
};
 
std::vector<Noisy> f()
{
    std::vector<Noisy> v = std::vector<Noisy>(3); // copy elision from temporary to v
    return v; // NRVO from v to the nameless temporary that is returned
}
 
void fn_by_val(std::vector<Noisy> arg)
{
    std::cout << "arg.size() = " << arg.size() << '\n';
}
 
int main()
{
    std::vector<Noisy> v = f(); // copy elision from returned temporary to v
    fn_by_val(f());             // and from temporary to the argument of fn_by_val()
}