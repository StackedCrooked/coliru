#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int>> m(10, vector<int>(5));
    
    for(int i = 0; i < 10*5; ++i) {
        m[i/5][i%5] = i;
    }
    
    for(auto&& row : m) {
        for(auto&& e : row) {
            cout << e << ", ";
        }
        cout << endl;
    }
    return 0;
}
