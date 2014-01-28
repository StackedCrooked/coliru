#include <iostream>

int A[10]; // array of 10 zeroes

int main()
{
    int index;
    while (std::cin >> index) // read index from stdin while not EOF
        A[index] += 1; // increment element at that index

    for (int i = 0; i != 10; ++i) std::cout << A[i]; // print array
}