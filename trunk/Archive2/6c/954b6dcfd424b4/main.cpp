#include <iostream>
using namespace std;
string addBinary(string a, string b) {
    const int M = a.size();
    const int N = b.size();
    const int L = max(M,N)+1;
    string res(L,0);
    //int i = M-1, j = N-1, k = L-1;
    for (int i = M-1, j = N-1, k = L-1, carry = 0; 
         i >= 0 || j >= 0 || carry > 0; --i, --j, --k) {
        int d1 = i >= 0 ? a[i]-'0' : 0;
        int d2 = j >= 0 ? a[j]-'0' : 0;
        carry += (d1+d2);
        res[k] = (carry % 2) + '0';
        carry /= 2;
    }
    if ('0' == res[0]) res = res.substr(1);
    return res;
}
int main() {
    string s="0", t="0";
		cout << addBinary(s, t) << endl;
	return 0;
}