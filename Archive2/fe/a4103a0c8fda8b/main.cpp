#include <vector>
#include <algorithm>
#include <utility>

std::vector<int> pf; // the sorted integers
std::vector<std::pair<int,int>> pairs;

for(int i = 0; i < pf.size();)
{
int mycount = std::count(pf.begin(), pf.end(), pf[i]);
// #1
pairs.push_back(std::make_pair(pf[i], mycount));
// #2
pairs.push_back(std::pair<int,int>(pf[i], mycount));
// #3
std::pair<int,int> p(pf[i], mycount);
pairs.push_back(p);
// skip the rest of the occurences of the same number
i += mycount;
}