#include <unordered_set>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;
using namespace std::placeholders;


int main()
{
    hash<int> h;
    for( int i=0 ; i < 30 ; ++i )
    {
        cout << "hash for " << i << "=" << h(i) << endl; 
    }

    hash<string> hs;
    for( int i=0; i<30; ++i) {
        stringstream ss;
        ss << i;
        cout << "hash for " << i << "=" << hs(ss.str()) << endl; 
    }
}