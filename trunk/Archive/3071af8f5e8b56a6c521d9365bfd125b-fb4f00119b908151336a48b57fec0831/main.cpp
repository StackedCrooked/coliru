#include <iostream>

int counter;

void loop(int i, const int n, const bool child=true) {
    if(child) goto child;
	for(;i<n;i++) {
		loop(i, n);
		child:;
	}
	counter++;
}

int main() {
	for(int i=0; i<10; ++i) {
		counter = 0;
		loop(0, i, false);
		std::cout << i << " " << counter << std::endl;
	}
}
