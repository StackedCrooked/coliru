#include <iostream>
#include <initializer_list>
using namespace std;

void doSomething(std::initializer_list<int> list) {

}

int main() {
    doSomething({2,3,6,8});
	return 0;
}