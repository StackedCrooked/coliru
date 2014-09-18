#include <bitset>

int main(){
 constexpr auto N = 512;
 std::bitset<N> b = 0xDEADC0DE; // OK
 std::bitset<N> c = b & 0xFFFF; // OK, but creates extra temporary bitset<512>
}