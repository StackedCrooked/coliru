#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

bool comp(const pair<string, pair<string, int>> &a, const pair<string, pair<string, int>> &b)
{
    string term1 = a.first;
    string term2 = b.first;

    return term1<term2;
}

int main()
{
    vector<pair<string, pair<string, int>>> v =
    {
        std::make_pair("Z", std::make_pair("a", 1)),
        std::make_pair("Y", std::make_pair("a", 2)),
        std::make_pair("X", std::make_pair("a", 3)),
    };
    
    std::sort(v.begin(), v.end(), comp);
    for (const auto& p : v)
    {
        std::cout << "(" << p.first << ","
                  << "(" << p.second.first << ","
                  << p.second.second << "))\n";
    }
}
