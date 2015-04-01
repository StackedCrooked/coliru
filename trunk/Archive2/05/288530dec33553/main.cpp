#include <iostream>
using namespace std;

struct MyStruct;

struct foo
{
    MyStruct *p;
};

int main() {
	foo f;
	delete f.p;
}