extern int arr[];
int (*p)[] = &arr;
int arr[] = {1,2,3};

#include <iostream>

int main() {
    std::cout << (*p)[0] << "\n";
}