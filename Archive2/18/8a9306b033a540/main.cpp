#include <iostream>

int A[10]; // array of 10 zeroes

int main()
{
    int index;
    while (std::cin >> index) // read index from stdin while not EOF
        A[index] += 1234; // increment element at that index

    std::cout << "Output:\n";
    for (int i = 0; i != 10; ++i) std::cout << A[i]; // print array
    std::cout << "\n----------\n\n";
}