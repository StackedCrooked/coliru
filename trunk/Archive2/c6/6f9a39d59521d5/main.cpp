#include <iostream>
#include <list>
#include <deque>
#include <vector>
using namespace std;

int main() {
    vector<int> data;
    int i;
    while (cin >> i)
        data.insert(data.begin(), i);
    while (!data.empty()) {
        cout << data.front() << ' ';
        data.pop_front();
    }
}
        
    