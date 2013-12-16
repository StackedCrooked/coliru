#include <iostream>

struct VOpt {
    VOpt() {}
    VOpt(VOpt const&) { std::cout << "copy"; }
    int x;
};

VOpt f(VOpt m) {
    m.x = 21;
    return m;
}

int main() {
    VOpt x;
    VOpt y = f(x);
    (void)y; // avoid unused variable warning
}
