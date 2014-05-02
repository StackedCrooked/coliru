#include <iostream>
#include <cassert>
using namespace std;

struct Foo {
    int a[3];
    
    public:
    Foo():a{-1,-1,-1} {}
};

int main() {
    Foo f;
    for (int i = 0; i < 3; ++i)
        cout << f.a[i] << " ";
        
  	return 0;
}