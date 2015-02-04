#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
public:
    static bool sort_f(int a, int b) {
        stack<int> sa, sb;
        if (a == 0)
            return false;
        else if (b == 0)
            return true;
        int tmp;
        while ((tmp = a % 10)) {
            sa.push(tmp);
            a /= 10;
        }
        while ((tmp = b % 10)) {
            sb.push(tmp);
            b /= 10;
        }
        // both have same size. Shit got serious
        while (!sa.empty() && !sb.empty()) {
            a = sa.top();
            b = sb.top();
            if (a > b)
                return true;
            else if (b > a)
                return false;
            sa.pop();
            sb.pop();
        }
        return sa.empty();
    }
    string largestNumber(vector<int> &num) {
        sort(num.begin(), num.end(), Solution::sort_f);
        string s;
        for (int v: num) {
            s += to_string(v);
        }
        return s;
    }
};

int main()
{
    Solution s;
    vector<int> v{41,23,87,55,50,53,18,9,39,63,35,33,54,25,26,49,74,61,32,81,97,99,38,96,22,95,35,57,80,80,16,22,17,13,89,11,75,98,57,81,69,8,10,85,13,49,66,94,80,25,13,85,55,12,87,50,28,96,80,43,10,24,88,52,16,92,61,28,26,78,28,28,16,1,56,31,47,85,27,30,85,2,30,51,84,50,3,14,97,9,91,90,63,90,92,89,76,76,67,55};
    std::cout << s.largestNumber(v) << std::endl;
    
    return 0;
}
