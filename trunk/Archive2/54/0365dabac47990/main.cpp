#include <iostream>
#include <string>
#include <vector>
#include <new>

using namespace std;

class C {
    int a,b,c;
public:
    C() { cout << "ctor" << endl; }
    ~C() { cout << "dtor" << endl; }
    void* operator new(size_t size) {
        cout << "op new " << size << endl;
        return ::operator new(size);
    }
    void operator delete(void* ptr) {
        cout << "op delete" << endl;
        ::operator delete(ptr);
    }
    void* operator new[](size_t size) {
        cout << "op new[] " << size << endl;
        return ::operator new(size);
    }
    void operator delete[](void* ptr) {
        cout << "op delete[]" << endl;
        ::operator delete(ptr);
    } 
};


int main() {
    C* c;
    cout << "sizeof(C)=" << sizeof(C) << endl;
    cout << "---------\n";
    c = new C;
    delete c;
    cout << "---------\n";
    c = new C[2];
    delete[] c;
    cout << "---------\n";    
}