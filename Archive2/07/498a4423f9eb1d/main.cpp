
typedef unsigned long long uint;
constexpr uint loop(uint x, uint k) {
    return k <= 1?x + k:loop(loop(x, k/2), k/2 + k%2);
}

template<int x>
class X {};
X<loop(0, uint{-1})> x;