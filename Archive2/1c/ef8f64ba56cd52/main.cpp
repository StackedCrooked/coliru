#include <iostream>           
#include <vector>
#include <thread>
#include <memory>

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
    vector<shared_ptr<void>> v;
    
    shared_ptr<A> ad = make_shared<A>();
    cout << "before push_back\n";
    v.push_back(ad);
    cout << "after push_back, before reset\n";
    ad.reset();   
    cout << "aftere reset, now clear vector and call dtor\n";
    v.clear();    
    cout << "before return\n";
    return 0;
}







