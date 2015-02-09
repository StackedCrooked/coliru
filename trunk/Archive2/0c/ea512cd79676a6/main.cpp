#include <map>
#include <iostream>
#include <string>
#include <iterator> // for std::prev

using namespace std; // for brevity

void test(const map<int,string>& data, int key)
{
    cout << "searching for " << key << endl;

    auto range = data.equal_range(key);
    auto it1 = range.first;
    auto it2 = range.second;

    if (it1 != it2)
        cout << "\tfound: " << it1->second << endl;

    auto closestPrior = (it1 != data.begin()) ? prev(it1) : data.end();
    auto closestAfter = it2;

    if (closestPrior != data.end())
        cout << "\tprior: " << closestPrior->second << endl;
    if (closestAfter != data.end())
        cout << "\tafter: " << closestAfter->second << endl;
}

int main()
{
    map<int, string> data;
    data[1] = "one";
    data[5] = "five";
    data[9] = "nine";

    for (int i=0; i<11; ++i)
        test(data, i);
}