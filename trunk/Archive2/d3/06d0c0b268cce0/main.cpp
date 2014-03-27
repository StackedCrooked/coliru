#include <iostream>
#include <typeinfo>

void show(const int (&array)[10]) {
    for (int& i : array)
        i = 0;
}

int main() {
    int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    show(x);
}