#include <iostream>
#include <cstdio>

int main ()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);    

    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        printf("%d ", i);
    }

    cout << endl;
    return 0;
}