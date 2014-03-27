#include <iostream>

void reset(int (&array)[10]) {
    for (int& i : array)
        i = 0;
}

int main() {
    int x[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    reset(x);
}