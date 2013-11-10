#include <functional>

int main() {
    std::function<void()> fnTest;
	for(auto i : undeclared) {
		fnTest = [i] {};
	}
}
