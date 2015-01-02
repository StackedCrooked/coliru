#include <iostream>
#include <vector>

enum TFoo { VAL1, VAL2 };

struct CFoo {
    TFoo mf;
    CFoo() { std::cout<<"CFoo()\n"; }
    CFoo(CFoo const&) { std::cout << "CFoo(CFoo const&)\n"; }
    CFoo(CFoo&&) { std::cout << "CFoo(CFoo&&)\n"; }
    CFoo(TFoo f) { std::cout<<"CFoo(TFoo f)\n"; }
    ~CFoo() { std::cout<<"bye\n"; }
};

int main() {
    std::vector<CFoo> v;
    v.push_back(VAL1);
}