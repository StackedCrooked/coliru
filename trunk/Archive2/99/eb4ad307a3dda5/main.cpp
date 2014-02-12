#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
using namespace std;

int main()
{
    vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
 
    auto lower = lower_bound(begin(data), end(data), 4);
    auto upper = upper_bound(begin(data), end(data), 4);
    auto range = equal_range(begin(data), end(data), 4);
 
    copy(lower, upper, ostream_iterator<int>(cout, " "));
    cout << endl;
    copy(range.first, range.second, ostream_iterator<int>(cout, " "));
}