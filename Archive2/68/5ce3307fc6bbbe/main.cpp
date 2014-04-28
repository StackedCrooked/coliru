#include <iostream>

int main() {

    char a = 'a';
	while(a < 'z') {
		std::cout << a + std::string(") ") << std::string("f'(x) = ") << std::endl;
		++a;
	}

	return 0;
}