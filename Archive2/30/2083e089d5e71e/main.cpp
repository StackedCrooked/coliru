#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct reg
{
    T val;

    void load(const T v) { val = v; }
    void add(const T v) { val += v; }
    void sub(const T v) { val -= v; }
    void inc() { ++val; }
    void dec() { --val; }

    void print() const
    {
        cout << hex << static_cast<uint64_t>(val) << endl;
    }
};

typedef reg<uint8_t> reg8;
typedef reg<uint16_t> reg16;

union reg2x8or16
{
    struct { reg8 A, B; };
    reg16 AB;
};

int main(int argc, const char *argv[])
{
    reg2x8or16 r;

    r.AB.load(0xBEEF);
    r.AB.print();
    r.B.load(0xCA);
    r.AB.print();
    r.A.load(0xFE);
    r.AB.print();
    r.A.print();
    r.B.print();
}