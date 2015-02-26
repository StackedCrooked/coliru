#include <iostream>
#include <memory>

using std::cout;
using std::endl;

template <typename T>
using make_array = T[];

int main()
{
    for (int i : make_array<int> {1, 2, 5})
        cout << i << endl;
    
    return 0;
}