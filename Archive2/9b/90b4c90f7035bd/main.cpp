#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

struct J {};

J fuck() {
    std::cout << "Called" << std::endl;
    return J();
}

void print(J x()) {
    x();
}

int main()
{
    print(fuck);
    return 0;
}