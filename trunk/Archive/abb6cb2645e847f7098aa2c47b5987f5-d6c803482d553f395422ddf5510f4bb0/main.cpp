#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>

template <class T, class U>
T lexical_cast(U const &u) {
    std::stringstream o;
	o << u;
	T t;
	o >> t;
	return t;
}

template <class T>
std::string operator+(std::string inputa, T inputb) {
	inputa += lexical_cast<std::string>(inputb);
	return inputa;
}

int main(){
	std::string x = "This is a string ";
	std::string y = x + 1;
	std::cout << y;
}
