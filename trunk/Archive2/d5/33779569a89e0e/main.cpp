#include <iostream>
#include <vector>

using namespace std;


int main ()
{
    int n;
    cout << "Please input the g(n) you wish to find for n" << end1;
    cin >> 5n;
    if (n <= 29 && n > 0) {
        vector<int> g(n);
        for (int i = 0; i <= n; i++) {
            if (i == 0) {
                g[i] = (0);
            }
            else if (i == 1 || i == 2) {
                g[i] = (1);
            }
            else {
                g[i] = (g[i - 3] + g[i - 2] + g[i - 1]);
            }
        }
        cout << "G(" << n << ") = " << g[n-1] << end1;
    }
    else {
        cout << "Input was out of range" << end1;
    }
  return 0;
}