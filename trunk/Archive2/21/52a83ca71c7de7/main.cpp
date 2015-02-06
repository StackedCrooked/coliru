#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Solution {
public:
    int numTrees(int n) {
        if (n<=1) { return 1; }
        vector<int> numArr(n,1);
        for (int i=2; i<=n; ++i) {
            numArr[i] = 0;
            for (int j=0; j<i; ++j) {
                numArr[i] += numArr[j]*numArr[i-1-j];
            }
        }
        return numArr[n];
    }
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    int inp = 1;
    Solution sol;
    int ret = sol.numTrees(inp);
    cout << "inp=" << inp << " ret=" << ret << endl;
}
