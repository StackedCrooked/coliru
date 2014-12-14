#include <iostream>
#include <numeric>

 
int main()
{
    int arr[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int n = 10;    
    int sum = std::accumulate(arr,arr+n,0);
    std::cout<<sum;
}