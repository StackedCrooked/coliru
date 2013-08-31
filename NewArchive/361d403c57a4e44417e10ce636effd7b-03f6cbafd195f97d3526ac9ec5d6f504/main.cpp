#include <iostream>
#include <vector>

void f(int& a) {
    a = 5;
}

int main() {
    std::vector<int> v;
    for(int i = 0; i < 10; ++i) {
        v.push_back(f(i));
    }
}