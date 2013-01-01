#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {

    std::srand(std::time(0));

    int random[100], i = 0,
        max = 19, 
        min = 3;

    do {
        random[i] = min + (std::rand() % (max - min + 1));
    } while (i++ < 100);

    for (int i = 0; i < 100; ++i) std::cout << random[i] << '\n';

}