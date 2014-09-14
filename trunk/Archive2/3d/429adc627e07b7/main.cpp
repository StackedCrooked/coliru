#include <string>
struct T1 {};
class T2 { 
    int mem;
 public:
    T2() {} // "mem" not in initializer list
};
int n; // A two-phase initialization is done
       // In the first phase, zero initialization initializes n to zero
       // In the second phase, default initialization does nothing, leaving n being zero
int main()
{
    int n;            // non-class: the value is undeterminate
    std::string s;    // calls default ctor, the value is "" (empty string)
    std::string a[2]; // calls default ctor, creates two empty strings
//    int& r;         // error: default-initializing a reference
//    const int n;    // error: const non-class type
//    const T1 nd;    // error: const class type with implicit ctor
    T1 t1; // ok, calls implicit default ctor
    const T2 t2; // ok, calls the user-provided default ctor 
                 // t2.mem is default-initialized (to indeterminate value)
}