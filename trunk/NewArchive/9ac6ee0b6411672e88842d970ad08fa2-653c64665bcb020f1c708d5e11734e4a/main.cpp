#include<iostream>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<iterator>
#include<utility>
#include <stdio.h>




int main (int argc, char* argv[])
{
    int arr[] = {1,3,5,6,8,0};
    
    int* p = &arr[0];
    
    while (*p != 0)
    {
        std::cout << *p++;
    }
    
   return 0;
}