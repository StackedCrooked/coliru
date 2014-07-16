#include <vector>
#include <cstdint>

using namespace std;

void test(uint16_t x) {
    vector<uint8_t> v;
	v.push_back(x >> 8);
	v.push_back(uint8_t{x >> 8});
	v.push_back(uint8_t(x >> 8));
}

int main() {
}