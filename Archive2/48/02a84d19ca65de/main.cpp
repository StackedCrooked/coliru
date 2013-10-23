#include <iostream>
#include <list>
#include <deque>
#include <vector>
using namespace std;

int main() {
    vector<int> data;
    int i;
    while (cin >> i)
        data.push_back(i);
    while (!data.empty()) {
        cout << data.back() << ' ';
        data.pop_back();
    }
}
        
    