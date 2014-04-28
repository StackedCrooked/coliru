#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <functional>

using namespace std;

struct Memory {
    void* alloc(size_t size) {
        return malloc(size);
    }
    void dealloc(void* p) {
        free(p);
    }
};

struct C {
    C() { cout << "bef"; throw 1; cout << "aft" << endl; }
};

struct D {
    D(int val) : val_(val) { }
    D(D&& d) { val_ = d.val_; d.val_ = 0; }
    int val_;
};

void* operator new(size_t size, Memory& memory, D&& d) {
    D my_d(move(d));
    void* p =  memory.alloc(size);
    cout << "new " << p << " " << size << endl;
    return p;
}

void operator delete(void* p, Memory& memory, D&& d) {
    cout << "d.val_ = " << d.val_ << endl;
    cout << "delete " << p << endl;
    memory.dealloc(p);
}

int main() {
    Memory m;
    try {
        C* c = new (m, D(5)) C;
        cout << "i don't" << endl;
        delete c;
    } catch(...) {
        cout << "exist" << endl;
    }
    return 0;
}
