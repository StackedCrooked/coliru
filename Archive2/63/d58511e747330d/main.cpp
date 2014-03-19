#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

size_t array_len(int arr[])
{
    return (sizeof(arr) / sizeof(*arr));
}
 
int main()
{
    vector<int> vec;
    auto it = back_inserter(vec);
    *it = 10;
    *it = 20;
    for(auto &i : vec)
        cout << i << " ";
    cout << endl;
    
    int arr[] = {0, 1, 2, 3};
    cout << array_len(arr) << endl;
    return 0;
}