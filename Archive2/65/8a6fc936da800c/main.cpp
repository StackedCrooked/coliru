extern int arr[];

#include <iostream>
int main()
{
    int (*p)[] = &arr;
    std::cout << (*p)[0] << "\n";
}

int arr[] = {1,2,3};