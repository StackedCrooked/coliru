#include <iostream>

void sort(int arr[], int n)
{
    int c = 0;

    for(int i = 0; i<n-1; ++i) {
        if (arr[i]>arr[i+1]) {
            c=arr[i];
            arr[i]=arr[i+1];
            arr[i+1]=c;
            i=0;
        }
    }

}

int main()
{
    int arr[4] = {3,1,2,4};
    std::cout << '\n';
    for (size_t i = 0; i < 4; i++)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
    
    ::sort(&arr[0], 4);
    
    std::cout << '\n';
    for (size_t i = 0; i < 4; i++)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}
