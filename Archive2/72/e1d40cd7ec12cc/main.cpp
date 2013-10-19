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


bool is_odd(int n) {
    return (n % 2) != 0;
}




int main()
{
 
    int arr[] = { 4, 2, 5, 1, 3 };
    vector<int> numbers(arr,arr+5);
    
    int num_odds;
    num_odds = std::count_if( numbers.begin(), numbers.end(), is_odd );
    
    cout << num_odds;    // prints 3
    
}