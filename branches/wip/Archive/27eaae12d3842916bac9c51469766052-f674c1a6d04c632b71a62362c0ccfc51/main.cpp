#include <iostream>


typedef int func_type(int, int);

func_type func;


int main() {
    std::cout << func(1, 2);
}

int func(int x, int y) {
    return x + y;
}

/*
func_type func {
    return x + y; // x and y???
}
*/