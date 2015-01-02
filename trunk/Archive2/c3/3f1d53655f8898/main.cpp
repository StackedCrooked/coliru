#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
  */
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        if (n<1) { return 0; }
        vector<int> sht(n, 0);

        sht[0] = triangle[0][0];
        for (int row=1; row<n; ++row) {
            sht[row] = sht[row-1]+triangle[row][row];
            for (int i=triangle[row].size()-2; i>0; --i) {
                sht[i] = min(sht[i-1], sht[i]) + triangle[row][i];
            }
            sht[0] = sht[0]+triangle[row][0];
        }

        return *(std::min_element(sht.begin(), sht.end()));
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    cout << '{';
    for (auto& el : vec) { os << el << ' '; }
    cout << '}';
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
   vector<vector<int>> tri;
   vector<int> t0 = {-1};
   tri.push_back(t0);
   vector<int> t1 = {2,3};
   tri.push_back(t1);
   vector<int> t2 = {1,-1,-3};
   tri.push_back(t2);
   cout << "triangle content:";
   cout << tri << endl;
   Solution sol;
   int ret = sol.minimumTotal(tri);
   cout << "ret=" << ret << endl;   
}
