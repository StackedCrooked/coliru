#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

vector<int>::const_iterator findelement(const vector<int> &ivec, int target)
{
auto it=ivec.begin();
while(it!=ivec.end())
{
    if(*it=target)
        return it;
    else ++it;
}
return ivec.end();
}
int main() {
    vector<int> numbers{1,2,3,4,5,6,7,8,9,10};
    auto iter=findelement(numbers,5);
    cout<<*iter;
    
    --iter;
    cout<<*iter; //I think the output should be 4, but the output is 134281917!
    return 0;
}