#include <iostream>
#include <vector>

struct A {
    A() { std::cout << "default constructed\n"; }
    A(A&&) { std::cout << "move constructed\n"; }
    A& operator=(A&&) { std::cout << "move assigned\n"; return *this; }
};

int main() {
    std::vector<A> v;
    std::cout << "emplace_back\n";
    v.emplace_back();
    std::cout << "emplace\n";
    v.emplace(v.begin());
    
    return 0;
}