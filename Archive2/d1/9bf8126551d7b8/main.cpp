#include <iostream>

int foo(int *test)
{
    test[0]=2;
    return test[0];
}

int main()
{
    int i,j = 0;
    int index[2] = {0,1};
    int arr[2] = {0,10};
    i = foo(arr);
    std::cout << i << "\t" << j << "\n" << std::endl;
    for(int i:index)
        std::cout << arr[i] << std::endl;
    return 0;
}