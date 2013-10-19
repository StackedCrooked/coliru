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
    
    if( std::all_of( numbers.begin(), numbers.end(), is_odd ) )
        cout << "all are odd numbers";
    else if( std::any_of( numbers.begin(), numbers.end(), is_odd ) )
    	cout << "at least one odd number";
    else if( std::none_of( numbers.begin(), numbers.end(), is_odd ) )
    	cout << "no odd numbers";

    
}