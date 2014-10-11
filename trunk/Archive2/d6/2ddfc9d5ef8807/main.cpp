#include <iostream>
int main() {
    for (auto i : { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765 })
        std::cout << i-42 << "\n"; // well, maybe the "-42" is a bit redundant
}
