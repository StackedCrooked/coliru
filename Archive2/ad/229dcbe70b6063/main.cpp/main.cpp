#include <iostream>
#include <type_traits>

#include <iostream>

struct noisy {
    int n;
    ~noisy() { std::cout << "destroy " << n << "\n"; }
};

struct s {
    noisy const & r;
};

int main() {
    std::cout << "create 1 on stack\n";
    s a {noisy{ 1 }};  // Temporary created and destroyed.

    std::cout << "create 2 on heap\n";
    s* p = new s{noisy{ 2 }};  // Creates dangling reference
}
