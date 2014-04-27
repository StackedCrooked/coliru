#include <iostream>
#include <cassert>
using namespace std;

int main() {
    assert(!"Should not be here");
    cout << "hello";
	return 0;
}