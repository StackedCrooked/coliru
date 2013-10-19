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


enum CmpMode { ascending, descending };
bool compare_mode( enum CmpMode mode, int a, int b )
{
    if(mode==ascending) return a < b;
    else                return a > b;
}




int main()
{
 
    int arr[] = { 4, 2, 5, 1, 3 };
    vector<int> numbers(arr,arr+5);
    // sort in any order
    std::sort( numbers.begin(), numbers.end(), 
               bind(compare_mode, descending, _1, _2) );


    for(auto n : numbers )
        cout << n << " ";
    cout << endl;
}