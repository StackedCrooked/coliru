#include <iostream>

int main() {
    int i = 5, j = 10;
    int *p = &i;
    int **pp = &p;
    (void*&)*pp= &j;
    std::cout << **pp;
}