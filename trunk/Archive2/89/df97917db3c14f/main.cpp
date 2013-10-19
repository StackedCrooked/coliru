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


bool differ_by_4(int a, int b) {
return abs(a - b) == 4;
}



int main()
{
 
    int arr[] = { 4, 2, 5, 1, 3 };
    vector<int> numbers(arr,arr+5);
    
    vector<int>::iterator it;
    it = std::adjacent_find( numbers.begin(), numbers.end(), differ_by_4 );
    if( it != numbers.end() ) {
        cout << *it << " and "; 
    it++; 
        cout << *it << " differ by 4";
    }

    
}