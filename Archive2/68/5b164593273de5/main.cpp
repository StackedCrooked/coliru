#include <iostream>
#include <vector>

using namespace std;


int main ()
{
      int n = 29; 
      if (n <= 29 && n > 0) {
        vector<int> g(n);
        for (int i = 0; i <= n; i++) {
            if (i == 0) {
                g[i] = (0);
                cout << (i << " = " << g[i]);
            }
            else if (i == 1 || i == 2) {
                g[i] = (1);
                cout << (i << " = " << g[i]);
            }
            else {
                g[i] = (g[i - 3] + g[i - 2] + g[i - 1]);
                cout << (i << " = " << g[i]);
            }
        }
    }
  return 0;
}