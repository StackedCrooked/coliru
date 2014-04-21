#include <iostream>
using namespace std;
    
template <typename T>
class template_class {
    T v;
    friend void foo(template_class<T> t) {
        t.v = 1;    // (1)can access the private member because it's a friend
        cout << t.v << endl;
        template_class<int> t1;
        t1.v = 2;   // (2)accessible if instantiated with [T=int]
        cout << t1.v << endl;
        template_class<char> t2;
        t2.v = 'c'; // (3)why accessible too even if instantiated with [T=int]?
        cout << t2.v << endl;
    }
};
    
int main() {
    template_class<int> t;  // (4)generate void foo(template_class<int> t)
    foo(t);
    return 0;
}