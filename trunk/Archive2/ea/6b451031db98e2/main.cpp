/*
ID: erdemtu2
PROG: friday
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int horwuul(int month, int year) {
    if (month == 2)
        return ((year % 4) || (!(year % 100) && ((year + 300) % 400))) ? 28 : 29;
    switch (month) {
    case 3:
    case 5:
    case 9:
    case 11:
        return 30;
        break;
    default:
        return 31;
        break;
    }
}

int main() {
    // freopen("friday.in", "r", stdin);
    // freopen("friday.out", "w", stdout);

    int a, i, j;
    cin >> a;
    if (a < 0)
        a = 0;
    if (a > 400)
        a = 400;

    int ans[7] = { 0 };

    int q = 0;
    for (i = 0; i < a; i++)
        for (j = 0; j < 12; j++) {
            ans[((q + 6) % 7)]++;
            q = (q + horwuul(j, i)) % 7;
        }

    for (i = 0; i < 7; i++) {
        cout << ans[(i + 6) % 7];
        cout << " ";
    }
    return 0;
}
