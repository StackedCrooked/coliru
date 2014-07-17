#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int>vstr = { 1, 2, 3, 4,4,5,5,5 };

    vstr.erase(std::adjacent_find(vstr.begin(), vstr.end()));
    for (auto&itr : vstr) {
        cout << itr << " ";
    }
}

