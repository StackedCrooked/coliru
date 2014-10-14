//============================================================================
// Name        : wer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
    int a, b, c, n;
    int p = 0;
    cin >> a >> b >> c;
    for (int i = 0; i <= c; ++i) {
        cin >> n; {
            if (n < a) {
                p = p + a -n;
            }
                else if (n > b) {
                    p = p + n - b;
                }
                else p = p + n;
            }
        }
        cout << p;
	return 0;
}