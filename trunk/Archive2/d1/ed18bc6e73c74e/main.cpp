#include <iostream>
#include <string>
#include <vector>

using namespace std;

void foo(const vector<int> &v)
{
    cout << v.size() << endl;
}

int main()
{
  foo({1,2,3});
    
}
