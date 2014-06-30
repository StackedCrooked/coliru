#include <iostream>

struct TRIPLE {
    int a;
    int b; 
    int c;
};

int main() {
    const int dim = 3;
    TRIPLE x[dim] {{1, 3, 4}, {3, 1, 3}, {9, 1, 5}};
    for (int i = 0; i < dim; ++i)
        std::cout << x[i].a
                  << x[i].b
                  << x[i].c
                  << '\n';
}