#include <iostream>
#include <vector>
#include <algorithm>

int p;

struct A {
    int q;

    bool operator()(int x, int y) {
        ++p;
        ++q;

        return x < y;
    }
};

int main(int argc, char** argv) {
    A a;

    p = 0;
    a.q = 0;

    std::vector<int> v = { 3, 1, 5, 6, 2, 9, 8 } ;
    std::sort(v.begin(), v.end(), a);

    std::cout << p << " " << a.q << "\n";

    return 0;
}
