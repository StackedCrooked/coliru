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
struct compare_mode { 
    enum CmpMode mode;
	compare_mode( enum CmpMode m ) : mode(m) {}
    bool operator() ( int a, int b ) {
        if(mode==ascending) return a < b;
        else                return a > b;
    }
};



int main()
{
 
    int arr[] = { 4, 2, 5, 1, 3 };
    vector<int> numbers(arr,arr+5);
    // sort in any order
    std::sort( numbers.begin(), numbers.end(), 
               compare_mode(descending) );


    for(auto n : numbers )
        cout << n << " ";
    cout << endl;
}