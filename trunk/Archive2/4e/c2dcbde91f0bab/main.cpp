#include <iostream>
#include <string>

std::string Typo(std::string s) {
    if(( rand() % 5) == 0) {
		int t = rand() % s.length();
		char a = s[t];
		s[t] = s[t+1];
		s[t+1] = a;
	}
	return s;
}


int main() {
	for(int i = 0; i < 100; i++) {
		std::cout << Typo("Hello") << std::endl;
	}
	return 0;
}