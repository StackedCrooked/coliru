#include <iostream>
#include <string>
#include <vector>

void foo(){
    foo();
}

int main() {
	foo();
	return 0;
}