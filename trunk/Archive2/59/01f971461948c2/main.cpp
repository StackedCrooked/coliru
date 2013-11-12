#include <iostream>
#include <climits>
using namespace std;

template<typename T, int Bits1, int Bits2>
class TwoTinyInts {
    static_assert(Bits1 + Bits2 <= sizeof(T)*CHAR_BIT,
                  "exceeding capacity of chosen type");
    T value;
    enum { Shift1 = 0 };
    enum { Mask1 = ~(~0u << Bits1) };
    enum { Shift2 = Bits1 };
    enum { Mask2 = ~(~0u << Bits2) };
public:
    TwoTinyInts() : value(0) {}
    void value1(int v) {
        value &= ~(Mask1 << Shift1);
        value |= (v&Mask1) << Shift1;
    }
    int value1() const {
        return (value >> Shift1) & Mask1;
    }
    void value2(int v) {
        value &= ~(Mask2 << Shift2);
        value |= (v&Mask2) << Shift2;
    }
    int value2() const {
        return (value >> Shift2) & Mask2;
    }
};

#include <cassert>

int main() {
    TwoTinyInts<unsigned short, 3, 4> testval;
    testval.value1(6);
    testval.value2(11);
    assert(testval.value1() == 6);
    assert(testval.value2() == 11);
    testval.value2(1);
    assert(testval.value1() == 6);
    assert(testval.value2() == 1);
    testval.value1(2);
    assert(testval.value1() == 2);
    assert(testval.value2() == 1);
    cout << "** all tests passed" << endl;
    
}
    
    