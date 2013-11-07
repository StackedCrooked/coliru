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
    // separate to odd numbers then even numbers
    vector<int>::iterator 
            pivot = std::partition( numbers.begin(), numbers.end(), is_odd );  // 3, 5, 1, 2, 4

    cout << "odd" << endl;
    for(auto it=numbers.begin(); it!=pivot; ++it )
        cout << *it << " ";
    cout << endl;
    
    cout << "even" << endl;
    for(auto it=pivot; it != numbers.end(); ++it )
        cout << *it << " ";
    cout << endl;
}