#include <iostream>
using namespace std;


//  Works
//template <typename type> using r_ptr = type *;

//  Fails
template <typename type> using r_ptr = type *__restrict__;


template <void (*fp)(r_ptr<int> ptr)>
void foo(){
    int x = 123;
    fp(&x);
}

void fp(r_ptr<int> ptr){
    cout << ptr[0] << endl;
}

int main(int argc, char* argv[]) {

    foo<fp>();
    


}
