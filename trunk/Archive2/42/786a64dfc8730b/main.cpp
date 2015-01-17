#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Res {
  int s;             // smallest element
  int l;             // largest element
  int m;             // median
};

Res function(vector<int>& v) {
    int sum = 0;
    for(int x : v) {
        sum += x;
    }
    Res res;
    res.m = sum / v.size();
    res.s = *min_element(begin(v), end(v));
    res.l = *max_element(begin(v), end(v));
    return res;
}

int main()
{
    std::vector<int> nums = {1, 2, 3};
    Res r = function(nums);
    cout << "Smallest element: " << r.s << '\n';
    cout<< "Largest element: " << r.l << '\n';
    cout<< "Median: " << r.m << '\n';
}
