#include <iostream>           
#include <vector>
#include <thread>
#include <new>
#include <algorithm>

using namespace std;

class A {
 public:
 A() {
     cout << "CTOR!\n";
 }
 ~A() {
    cout << "~DTOR!\n";   
 }
    
};

int main ()
{
    shared_ptr<A> ad;
    ad.reset(new A);
//    ad = make_shared<A>(new A);
    cout << "TROLOLO\n";
    return 0;
}






















