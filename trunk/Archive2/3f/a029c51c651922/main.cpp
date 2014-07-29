#include <iostream>
#include <limits>

int main() {
    for(int i = std::numeric_limits<int>::max() - 5; i > 0; ++i) {
        std::cout << "Hi\n";
    }
}
