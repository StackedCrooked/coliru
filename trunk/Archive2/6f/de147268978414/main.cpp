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

void do_something(int a_number)
{
    cout << a_number << "\n";
}


void accumulate_number(int *dest, int a_number)
{
*dest += a_number;
}




int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vector<int> numbers(arr,arr+5);
    int total = 0;
    std::for_each(numbers.begin(), numbers.end(), 
                std::bind(accumulate_number, &total, _1) );
    cout << total;
}