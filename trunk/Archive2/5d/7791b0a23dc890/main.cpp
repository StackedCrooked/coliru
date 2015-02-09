#include <type_traits>
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    unordered_map<int, int> z;
    unordered_map<int, int> m{{1,2}, {2,3}};
    
    cout << sizeof(z) << " " << sizeof(m) << endl;
}