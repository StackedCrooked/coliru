#include <iostream>
#include <cstdio>
#include <map>
#include <iomanip>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

class C
{
    public:
    
    C(const void *buffer, uint32_t size){}    
};

int main()
{
    vector<uint32_t> v;
    C c(&v[0], v.size());
    
    return 0;
}
