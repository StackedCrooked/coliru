#include <map>
#include <string>
#include <iostream>

using namespace std;

class SortCriterion
{
    bool ascending;
public:
    SortCriterion(bool sorting_type): ascending(sorting_type){};
    // if operator below is not marked const, 
    // clang++ spits a compile-time error on insert
    // however g++ compiles it ok
    bool operator()(int x, int y) const
    {
        if(ascending) // ascending
            return x<y;
        else
            return x>y;
    }
    
    bool operator()(int x, int y)
    {
        if(!ascending) // ascending
            return x<y;
        else
            return x>y;
    }
};

int main()
{
    map<int, string, SortCriterion> m(SortCriterion(false)); // ascending

    m.insert({1,"one element"}); // clang++ compile error here
    m.insert({2,"another element"});
    for(auto elem: m)
        cout << elem.first << ": " << elem.second << endl;
}
