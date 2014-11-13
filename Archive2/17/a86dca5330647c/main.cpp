#include <map>
#include <iostream>
using namespace std;

    
int main() {
    
    map<int, int> m { {1,1}, {2, 2}, {3, 3} };
    for (auto& it : m) {
        cout << it.first << " " << it.second << endl;
    }
}
    