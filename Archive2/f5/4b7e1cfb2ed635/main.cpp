#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename T>
    inline void print(const T& ar, char sep = ' ', char end = '\n')
    {
        for (const auto& x : ar)
            cout << x << sep;
        cout << end;
    }
int main() {
    vector<int> ar={1,2,3,4,5,6,7,8,9,10};

    print(ar);
    int count=0;

    ar.erase(remove_if(ar.begin(),ar.end(),[count](int x)mutable
    {
        return ++count==3;
    }),ar.end()); 
  
    print(ar);
  
    return 0;
} 
