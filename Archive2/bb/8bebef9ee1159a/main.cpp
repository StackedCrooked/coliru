#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vi{1, 2, 3, 4};
    for (auto itr = vi.begin(); itr != vi.end(); ++itr)
        cout << *itr << endl;
}