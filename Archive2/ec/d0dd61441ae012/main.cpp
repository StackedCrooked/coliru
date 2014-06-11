#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    using namespace std;
    
    vector<int>     v1{ 3, 5, 8, 2, 4 };
    vector<double>  v2{ 2.9, 5.4, 2.1, 3.3 };
    vector<string>  v3{ "hello", "world", "apple" };

    cout << *minmax_element(v1.begin(), v1.end()).second << endl;
    cout << *minmax_element(v2.begin(), v2.end()).second << endl;
    cout << *minmax_element(v3.begin(), v3.end()).second << endl;
}