#include <iostream>
using namespace std;

//  Works
//template <typename type> using r_ptr = type *;

//  Fails
template <typename type> using r_ptr = type *__restrict__;


template <int x>
class MyObj{
public:
    void foo(r_ptr<int> ptr) const;
    
};


template <>
void MyObj<3>::foo(r_ptr<int> ptr) const{
    cout << "asdf" << endl;
}


int main(int argc, char* argv[]) {

    MyObj<3> x;
    x.foo();


}
