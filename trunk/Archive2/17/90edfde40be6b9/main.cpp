#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

struct mycomparer 
{
    bool operator () (string const& lhs, 
                      pair<string const, int> const& rhs) 
    {
        return lhs == rhs.first;
    }

    bool operator () (pair<string const, int> const& lhs,
                      string const& rhs) 
    {
        return lhs.first == rhs;
    }
};

int main()
{
    
    vector<string> custom_list;
    map<string, int> master_list;
    vector<string> target_list;

    std::sort(custom_list.begin(), custom_list.end());
    std::set_intersection(custom_list.begin(), 
                          custom_list.end(), 
                          master_list.begin(),
                          master_list.end(), 
                          back_inserter(target_list), 
                          mycomparer());
}