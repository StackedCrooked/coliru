#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    vector<int> x{5};
    copy(x.begin(), x.end(), ostream_iterator<int>(cout, "\n"));
    
}
