#include <iostream>
#include <string>

int main() {
    long l1 = std::stof("4.2e+7");
    long l2 = std::stof("3E+7");
    long l3 = 3E7;
    printf("%d\n%d\n%d\n", l1, l2, l3);

    return 0;
}