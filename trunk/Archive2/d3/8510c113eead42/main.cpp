#include <iostream>
using namespace std;

class X {
public:
    X(){
        cout<<"default ctor X====="<<endl;
    }

    X(X&){
        cout<<"X&======="<<endl;
    }

    X(const X&){
        cout<<"const X&======="<<endl;
    }
};
     
 int main() {
    // your code goes here
    X x;
    const X x2((const X)x);
     
    X x3(x2);
     
    return 0;
}