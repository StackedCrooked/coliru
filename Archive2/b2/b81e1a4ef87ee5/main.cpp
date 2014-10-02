#include <iostream>
 using namespace std;
 
int modInverse(int a, int m) {
    a %= m;
    for(int x = 1; x < m; x++) {
        if((a*x) % m == 1) return x;
    }
}

int main(void) {
	cout<<mul_inv(42, 2017)<<endl;
	return 0;
}
 