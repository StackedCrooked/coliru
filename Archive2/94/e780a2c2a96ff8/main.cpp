#include <iostream>

    int theProduct(int anArray[], int n) {
        if (n <= 0)
            return 0;
        else if (n == 1)
            return anArray[0];
        else
            return anArray[n-1] * theProduct(anArray, n - 1);
    }
    
int main() {
    int myArray[3] = {1, 2, 3};
    std::cout << theProduct(myArray, 3);
}