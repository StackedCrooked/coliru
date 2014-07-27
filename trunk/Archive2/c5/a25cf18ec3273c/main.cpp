#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec(100);

    generate(vec.begin(), vec.end(), [i = 0]() mutable { return i++; });
    
    for (auto x: vec) {
        cout << x << ' ';
    }
}