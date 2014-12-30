#include <cstdlib>

int maximum(int num1, int num2, double num3) {
    int largest;
    if (num1 > num2)
       largest = num1;
    else
       largest = num2;
    if (num3 > largest)
       largest = num3;
    return largest;
}

int main() {
    return max(rand(), rand(), rand());
}
