#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::placeholders;

void sum(int& a, int b)
{
    a += b;
}

int main()
{
    vector<int> v = { 10, 20, 30 };
    int total = 0;
    for_each(begin(v), end(v), bind(sum, ref(total), _1));
    cout << total << endl;
    return 0;
}