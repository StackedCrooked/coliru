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

vector<int> divProduct(vector<int>& vec)
{
    long product = 1;
    unsigned zero_indx;
    unsigned zeros = 0;
    for (unsigned i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == 0)
        {
            ++zeros;
            zero_indx = i; 
        }
        else
            product *= vec[i];
    }

    vector <int> ret(vec.size(), 0);

    if (zeros <= 1)
    for (unsigned i = 0; i < vec.size(); ++i)
        ret[i] = zeros == 0 ? product / vec[i] : i == zero_indx ? product : 0;

    return ret;
}


// test bench
/*
int main()
{
    {
        vector <int> vec = { 1, 2, 3, 4, 5};
        
        vector <int> ret = divProduct(vec);
        for (auto i : ret) cout << i << " ";
    }
    cout << endl;
    {
        vector <int> vec = { 1, -2, 3, -4, 5};
        
        vector <int> ret = divProduct(vec);
        for (auto i : ret) cout << i << " ";
    }
    cout << endl;
    {
        vector <int> vec = { 1, 2, 0, 4, 5};
        
        vector <int> ret = divProduct(vec);
        for (auto i : ret) cout << i << " ";
    }
    cout << endl;
    {
        vector <int> vec = { 1, 0, 3, 0, 5};
        
        vector <int> ret = divProduct(vec);
        for (auto i : ret) cout << i << " ";
    }
    return 0;
}
*/

int main()
{
    //double d = 0.375;
    //double e;
    long m = 1L << 52;
    
    cout << setprecision(25) << (3 * m) % 10 * 100 << endl;
    cout << setprecision(25) << (7 * m) % 100 * 10 << endl;
    cout << setprecision(25) << (5 * m) % 1000 * 1 << endl;
    
    string s = "375";
    
    unsigned i = 0;
    unsigned size = s.size();
    unsigned sum = 0;
    while (i < size)
    {
        cout << s[i] - '0' % pow(10, i + 1) * pow(10, size - 1) << endl;
        ++i;
    }
    
    
    
    
    
}