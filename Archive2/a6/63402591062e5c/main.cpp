#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct Foo {
    int member;
    operator int() { return member; }    
};


int main()
{
    // 초기값 세팅 
    vector<Foo> v;
    for (int i = 0; i <= 10; ++i) {
        Foo f;
        f.member = i;
        v.push_back(f);   
    }
    
    
    // for_each
    {
        int sum = 0;
        
        for_each(v.begin(), v.end(), [&sum](const Foo &f) {
           sum += f.member;
        });
        cout << "sum : " << sum << endl;
    }
    
    // accumulate
    {
        int sum = accumulate(v.begin(), v.end(), 0);
        cout << "sum : " << sum << endl;
    
    }
    
}
