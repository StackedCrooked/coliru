#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
int n=9;


for (int x = 0; x <= n; x++) {
if (n == x + (x + 1) + (x + 2)) {
cout << x + 2 << " " << x + 1 << " " << x << endl;
exit(0);
}
}
cout << -1 << endl;
return 0;
}