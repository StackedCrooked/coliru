#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;

struct accumulate_multiply {
    int *sum;
	int *product;
	accumulate_multiply(int *s,int *p)	{
         sum = s; product = p; 
    }
    
    void operator() (int a_number) { 
        *sum += a_number;  
        *product *= a_number; 
    }
};





int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vector<int> numbers(arr,arr+5);
    int total = 0, product =1 ;
    std::for_each(numbers.begin(), numbers.end(), 
                accumulate_multiply( &total, &product )  );
    cout << total << " " << product;
}