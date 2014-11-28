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
    int a = 10;
    int arr[a];
    a[9] = 1;
    cout << a[9] << endl;
    return 0;
}







