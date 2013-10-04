#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct Number
{
    int i;
    string s;
};

int main()
{   
    vector<Number> vec = {{2, "two"}, {8, "eight"}};

    sort( vec.begin(), vec.end(), [](Number const& L, Number const& R){
        return L.i < R.i;
    });
    cout << vec.front().i << ", " << vec.back().i << "\n";  // 2, 8

    sort( vec.begin(), vec.end(), [](Number const& L, Number const& R){
        return L.s < R.s;
    });
    cout << vec.front().s << ", " << vec.back().s << "\n";  // eight, two
}
