#include <iostream>
#include <vector>

struct S
{
    S() { std::cout << i++ << std::endl; }
	static int i;
private:
	S( const S& ) { std::cout << "copy" << std::endl; }
};

int S::i = 0;

int main() {
	
	std::vector<S> s(10);
	return 0;
}