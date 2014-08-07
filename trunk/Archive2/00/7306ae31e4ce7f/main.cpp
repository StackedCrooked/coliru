#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> a;
    auto i = a.begin();
    vector<int>::const_iterator j = i;
}
