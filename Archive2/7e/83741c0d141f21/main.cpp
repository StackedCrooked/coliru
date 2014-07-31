//code

#include <iostream>
#include <algorithm>
#include <chrono>
#include <functional>
#include <vector>


using namespace std;

void testSpeedFun(const vector<unsigned> & vals, std::function<unsigned(unsigned)> fun) {
    const auto start = chrono::high_resolution_clock::now();

    for(const unsigned & val: vals) {
        fun(val);
    }

    const auto end = chrono::high_resolution_clock::now();

    auto diff = end - start;
    cout << "elapsed:" << chrono::duration <double, nano> (diff).count() << " ns" << endl;
}


struct byte {
    bool bit0 : 1;
    bool bit1 : 1;
    bool bit2 : 1;
    bool bit3 : 1;
    bool bit4 : 1;
    bool bit5 : 1;
    bool bit6 : 1;
    bool bit7 : 1;
};

unsigned t1(unsigned t) {
    union UU {
        unsigned _t;
        byte tab[sizeof(t)];
    } UU;
    UU._t = t;

    return accumulate(begin(UU.tab), end(UU.tab), 0u, [](unsigned & uh, const byte & by) {
        uh += by.bit0 + by.bit1 + by.bit2 + by.bit3 + by.bit4 + by.bit5 + by.bit6 + by.bit7;
        return uh;
    });
}


unsigned t2(unsigned n) {
    unsigned c;
    for(c = 0; n; c++) {
        n &= n - 1;
    }
    return c;
}

vector<unsigned> genTestValues(unsigned size) {
    vector<unsigned> out(size);
    iota(begin(out), end(out), size);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(begin(out), end(out), g);

    return out;
}


int main() {
    const vector<unsigned> & out = genTestValues(100000);


    function<void()> runTest1 = bind(testSpeedFun, out, t1);
    function<void()> runTest2 = bind(testSpeedFun, out, t2);

    runTest1();
    runTest2();

    return 0;
}

