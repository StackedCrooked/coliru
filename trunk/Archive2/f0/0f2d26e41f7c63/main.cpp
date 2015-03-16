#include <iostream>
#include <string>
#include <vector>
#include <new>

using namespace std;

class C {
public:
    C() { cout << "ctor" << endl; }
    ~C() { cout << "dtor" << endl; }
    void* operator new(size_t size) {
        cout << "op new" << endl;
        return ::operator new(size);   
    }
    void operator delete(void* ptr) {
        cout << "op delete" << endl;
        ::operator delete(ptr);   
    }    
};


int main() {
    C* c;
    c = new C();
    delete c;
}