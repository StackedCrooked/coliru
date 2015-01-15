#include<iostream>
#include<string>
using namespace std;
int q;
int fun1(int& x){
for (; x < 20;)
    { x++; cout << x << endl;}
	cin >> x;
	return 0;
}
int main(){
		cin >> q;
		fun1(q);	
}