#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <deque>
#include <stack>

int main() {

    std::vector<int> a;
	for (int i = 0; i < 100; i++){
		a.push_back(i);
		std::cout << a.capacity() << '\n';
	}
}