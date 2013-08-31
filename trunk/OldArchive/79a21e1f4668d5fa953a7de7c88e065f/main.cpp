#include <iostream>
#include <memory>

using std::cout;
using std::endl;

template <typename T>
using alias = T;

int main()
{
    for (int i : alias<int[]> {1, 2, 5})
        cout << i << endl;
    
    return 0;
}