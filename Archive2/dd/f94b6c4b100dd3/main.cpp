#include <iostream>

bool fun() {
    @try {
        return true;
    } @finally {
        return false;
    }
}

int main() {
    std::cout << fun() << '\n';
    return 0;
}
