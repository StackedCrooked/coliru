#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

    vector<vector<int>> v1
    {
        {1, 1},
        {2, 7},
        {3, 3}
    };

    for (auto r = v1.begin(); r != v1.end(); )
    {
        if (!r->size())
            continue;

        auto k = r->front();

        bool equal = all_of(r->begin(), r->end(), [&k](int x)
        {
            return x==k;
        });

        for (auto c = r->begin(); c != r->end(); c++)
            cout << *c << " ";

    	cout << " : " << equal  << "\n";


        if (equal)
            r = v1.erase(r);
        else
            ++r;
    }

    cout << "\n----\n";

    for (auto r = v1.begin(); r != v1.end(); r++)
    {
        for (auto c = r->begin(); c != r->end(); c++)
        {
            cout << *c << " ";
        }
        cout << "\n";
    }
}