#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Loop between 1 and 5
int iii=1;
while (iii<=5)
{
    // loop between 1 and iii
    int jjj = 1;
    while (jjj <= iii)
        cout << jjj++;
 
    // print a newline at the end of each row
    cout << endl;
    iii++;
}