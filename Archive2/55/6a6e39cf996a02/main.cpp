#include <chrono>
#include <iostream>
#include <memory>
using namespace std;

struct icic_algo {
    icic_algo(int c) {
        cout << "enter ctor" << endl;
        int* p = new int(5);
        if (c == -1) {
            throw 1;
        }
        delete p;
        cout << "success ctor" << endl;
    }
    ~icic_algo() { cout << "dtor" << endl; }
};

int main() {
    unique_ptr<icic_algo> algo;
    try {
        algo.reset(new icic_algo(-1));
    } catch (int i) {
        cout << i << endl;
    }
}