#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int>> m(10, vector<int>(5));
    for(auto&& row : m) {
        for(auto&& e : row) {
            cout << e << ", ";
        }
        cout << endl;
    }
    return 0;
}
