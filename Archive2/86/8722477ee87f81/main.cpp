#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    map<int, int> data;
    data[1] = 4;
    data[5] = 10;
    data[6] = 14;
    data[11] = 3;
    
    vector<pair<int, int>> finalPairs(data.size());
    std::copy(data.begin(), data.end(), finalPairs.begin());

    
    std::sort(finalPairs.begin(), finalPairs.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
    
    for(auto p : finalPairs)
    {
        cout << p.first << ": " << p.second << endl;
    }
}

