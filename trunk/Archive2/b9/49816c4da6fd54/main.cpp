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

union reg8x2or16
{
    struct { reg8 H, L; };
    reg16 HL;
};

int main(int argc, const char *argv[])
{
    reg8x2or16 r;

    r.HL.load(0xBEEF);
    r.HL.print();
    r.L.load(0xCA);
    r.HL.print();
    r.H.load(0xFE);
    r.HL.print();
    r.H.print();
    r.L.print();
}