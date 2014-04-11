#include <iostream>

using namespace std;
 
int main()
{
    int i = 0;
    do i++;
    while (i < 10);
 
    cout << i << '\n';
 
    i = 11;
    do i = i + 10;
    while (i < 10); // the condition is false before the loop
 
    cout << i << '\n';
 
    int j = 2;
    do {
        j += 2;
        cout << j << " ";
    } while (j < 9);
}