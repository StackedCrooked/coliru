#include <iostream>

int main() {
    int A[2][2] = {0,1,2,3};
    std::cout << *(int*)(A+1) << std::endl;
}