#include <vector>
#include <iostream>
using namespace std;
int main()
{ 
    const int max_n = 73411 - 11437;
    vector<bool> sieve(max_n, 0);
 
    for (auto n: sieve) {
        cout << n << ' ';
    }
}