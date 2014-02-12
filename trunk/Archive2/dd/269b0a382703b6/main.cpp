#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string str("0");
    vector<int> vec;
    int upper_bound = str.size()-(3-vec.size());
    int i = 0;

    if ( i < upper_bound ) // Line 1
        cout << "i < upper_bound - 1\n";
    else
        cout << "pass\n";

    if ( i < (str.size()-(3-vec.size())) ) // Line 2
        cout << "i < upper_bound - 2\n";
    else
        cout << "pass\n";        

    return 0;
}