#include <utility>

void MySort(int* T, int n)
{
   for (int m = 0; m<=n-2; ++m) //will run n+1
   {
     int j = m; // will run n times
     for (int k = m+1 ; k<= n-1; ++k) //will run n^2 +n
     {
        if (T[k] < T[j]) j = k; //will run n^2 times
     }
     std::swap(T[m], T[j]); //will run 3*n times
   }
} 



#include <algorithm>
#include <iterator>
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> data = {{1,2,3,4,5}};
    do {
        std::array<int, 5> copy = data;
        MySort(&copy[0], 5);
        
        if (std::is_sorted(copy.begin(), copy.end())) {
            std::cout << '{'<<data[0]<<data[1]<<data[2]<<data[3]<<data[4]<<"}\tCORRECT\n";
        } else {
            std::cout << '{'<<data[0]<<data[1]<<data[2]<<data[3]<<data[4]<<'}';
            std::cout << '{'<<copy[0]<<copy[1]<<copy[2]<<copy[3]<<copy[4]<<'}'<<'\n';
        }
        
    } while ( std::next_permutation(data.begin(), data.end()) );
}