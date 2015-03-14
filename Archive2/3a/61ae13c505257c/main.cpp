#include <iostream>
using namespace std;

struct Foo
{
    int i[0];
};

int main() {
	// your code goes here
	Foo f1;
    Foo f2[5];
	cout << sizeof(f1) << endl;
    cout << sizeof(f2) << endl;
	return 0;
}
