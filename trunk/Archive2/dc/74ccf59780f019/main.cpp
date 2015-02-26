#include <vector>
#include <iostream>
#include <algorithm>
 #include <stdio.h>
int main()
{
    std::vector<char> v({a,b,c});
    std::reverse(std::begin(v), std::end(v));
    std::cout << v[0] << v[1] << v[2] << '\n';
 
    int a[] = {4, 5, 6, 7};
    std::reverse(&a[0], &a[4]);
    std::cout << a[0] << a[1] << a[2] << a[3] << '\n';
}