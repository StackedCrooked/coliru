#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;

struct Shell
{
    int id;
    Shell (int ID) : id(ID) { }
};

bool compare_by_id(const Shell &a, const Shell &b)
{
    return a.id < b.id;
}


int main()
{

    vector<Shell> shells = { 5, 2, 3, 1, 4 };
    
    std::sort(shells.begin(), shells.end(), compare_by_id );
    
    for(Shell s:shells)
        cout << s.id << " ";
    cout << endl;

}