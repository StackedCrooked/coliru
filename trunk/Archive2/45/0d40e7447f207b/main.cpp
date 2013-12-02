#include <iostream>
using namespace std;

namespace {
    constexpr double FLUX_CAPACITOR_OUTPUT = 1.21;
};

template<typename T> void nike(const T &val) {
	cout << val << endl;
}

int main() {
	nike(FLUX_CAPACITOR_OUTPUT);
}