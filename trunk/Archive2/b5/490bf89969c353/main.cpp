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


bool differ_by(int a, int b, int target_difference) {
    return abs(a - b) == target_difference;
}



int main()
{
 
    int arr[] = { 4, 2, 5, 1, 3 };
    vector<int> numbers(arr,arr+5);
    
    int diff = 2;
    vector<int>::iterator it;
    it = std::adjacent_find( numbers.begin(), numbers.end(), bind(differ_by, _1, _2, diff) );
    if( it != numbers.end() ) {
        cout << *it << " and "; 
        it++; 
        cout << *it << " differ by " << diff << endl;
    }

    
}