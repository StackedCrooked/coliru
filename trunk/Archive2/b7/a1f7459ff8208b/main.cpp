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

template<class T, class InputIterator> 
T sum( InputIterator first, InputIterator last, T tot )
{
    for( ; first != last; ++first )
    {
        tot += *first;
    }
    return tot;
}



int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vector<int> numbers(arr,arr+5);
    cout << sum(numbers.begin(), numbers.end(), 0);
}