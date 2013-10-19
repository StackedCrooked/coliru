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


int sum( const vector<int> &v )
{
    int tot = 0;
    for( vector<int>::const_iterator it = v.begin(); it != v.end(); ++it )
    {
        tot += *it;
    }
    return tot;
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vector<int> numbers(arr,arr+5);
    cout << sum(numbers);

}