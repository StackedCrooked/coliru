#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef vector<int> PrefList;
typedef map<int, PrefList> PrefMap;
typedef multimap<int, int> Matching;

map<int, int> CHcapacity ={{1,1},{2,1},{3,1}};
PrefMap PrefCHLists = {{1,{5,4,6}},{2,{4,6,5}},{3,{4,5,6}}};
PrefMap PrefONLists = {{4,{2,1,3}},{5,{3,1,2}},{6,{1,3,2}}};
int main()
{
    Matching match={{1,4},{2,5},{3,6}};
   Matching final=RVV(match);
}

Matching RVV(Matching m){
    Matching mT=m;
    map<int, int> S;
    return mT;
}
