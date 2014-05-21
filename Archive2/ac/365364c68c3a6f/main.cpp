#include <set>
#include <string>
#include <iostream>
#include <functional>

using namespace std;
typedef set<string, greater<string> > DecreasingStringSet;

int main()
{
    DecreasingStringSet s;
    s.insert("one");
    s.insert("two");
    s.insert("three");
    s.insert("four");
    for (auto x : s){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
