#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

const pair<int, string> a[] = {
    std::make_pair(1, "jedna")
};

int main()
{
    map<int, string> m;
    //map<int, string>::iterator it = foo.begin();
    std::copy(a, a + sizeof(a)/sizeof(a[0]), inserter(m,m.end()));
    cout << m[1] << endl;
}
