#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct unequal_zero { bool operator()(double x) { x != 0.0; } };

int main() {
    vector<int> x;
    x.push_back(1);
    x.push_back(0);
    x.push_back(4);
    x.push_back(1);
    x.push_back(0);
    double data[5] = { 1.1, 3.3, 4.4, 1.1, 2.3 };
    
    int cnt = count_if(&data[0], &data[5], unequal_zero());
    cout << cnt << endl;
//    sort(&data[0], &data[5]);
    for (double *p = &data[0]; p != &data[5]; ++p)
        cout << *p << endl;
}
        
    