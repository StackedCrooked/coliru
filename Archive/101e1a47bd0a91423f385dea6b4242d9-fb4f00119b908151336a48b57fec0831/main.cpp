#include <iostream>

int counter;

void child(int i, const int n) {
    goto child;
    for(i=0;i<n;i++) {
		child(i, n);
		child:;
	}
	counter++;
}

void parent(const int n) {
    int i;
    for(i=0;i<n;i++) {
		child(i, n);
	}
	counter++;
}

int main() {
    parent(10);
	std::cout << counter << std::endl;
}
