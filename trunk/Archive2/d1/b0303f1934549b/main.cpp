#include <bitset>
#include <iostream>

static const int size = 64;

int main(){
    std::bitset<size> res(1);
	res <<= 50;

	std::bitset<size> m1;
	m1.set();

	std::bitset<size> i = res ^ m1;
	std::bitset<size> c = (res & m1)<<1;
	res = i;

	do {
		i = res ^ c;
		c = (res & c) << 1;
		res = i;
	} while (c.count());
	std::cout << res;
}
