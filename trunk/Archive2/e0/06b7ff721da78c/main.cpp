#include <iostream>
#include <array>
using namespace std;
 
struct foo {
    double a[3];
	foo(double x, double y, double z) : a({x, y, z}) {}
};
 
int main() {
	foo f(2, 5, 8);
	cerr << f.a[0] << " " << f.a[1] << " " << f.a[2] << endl;
	return 0;
}