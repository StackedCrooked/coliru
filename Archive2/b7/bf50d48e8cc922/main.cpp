#include <iostream>
#include <iomanip>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <limits>
#include <time.h>
#include <random>
#include <functional>

using namespace std;

pair<int, int> findSumTo100(vector<int> & vec)
{
    int i, j, k = 1;
    bool bFound = false;
    while (!bFound && k < 100)
    {
        i = 0;
        j = i + k;
        while (!bFound && j < 100)
        {
            if (vec[i] + vec[j] == 100)
                bFound = true;
            else
                ++i, ++j;
        }
        ++k;
    }
    return bFound ? make_pair(i, j) : make_pair(-1, -1);
}

pair<int, int> findSumTo100_linear(vector<int> & vec)
{
    unordered_map<int, vector<unsigned>> m;
    unsigned vsize = vec.size();
    unsigned min_dist = vsize;
    pair<int, int> ret = make_pair(-1, -1);

    for (unsigned i = 0; i < vsize; ++i)
    {
        m[vec[i]].push_back(i);
        auto it = m.find(100 - vec[i]);
        if (it != m.end()) for (auto j : it->second)
        {
            unsigned d = abs(j - i);
            if (d < min_dist)
            {
                min_dist = d;
                ret = make_pair(i, j);
            }
        }
    }
    
/*
    for(unsigned i = 0; i < vsize; ++i)
    {
        auto it = m.find(100 - vec[i]);
        if (it != m.end()) for (auto j : it->second)
        {
            unsigned d = abs(j - i);
            if (d < min_dist)
            {
                min_dist = d;
                ret = make_pair(i, j);
            }
        }
    }
*/    return ret;
}


// test bench
int main()
{
    random_device rd;
    minstd_rand gen(rd());
    uniform_int_distribution<int> distrib(-95, 105);    
    auto get_next_ran = bind(distrib, gen);

    vector<int> vec;   
    for (int i = 0; i < 100; ++i)
    {
        int r = get_next_ran();
        cout << i << " " << r << endl;
        vec.push_back(r);
    }
    
    cout << endl;
    auto p = findSumTo100(vec);
    cout << "closest indexes: " << p.first << " " << p.second << endl;
    p = findSumTo100_linear(vec);
    cout << "closest indexes: " << p.first << " " << p.second << endl;  

    return 0;
}
