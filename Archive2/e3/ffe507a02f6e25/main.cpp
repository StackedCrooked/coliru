#include <iostream>
using namespace std;    	// Recursive Fibonacci
unsigned long Fibo(int n) {	// how far can you go?
  if (n==0||n==1) return n;		
  else return Fibo(n-1) + Fibo(n-2);
}
int main() {
  int num=100, n=0;
  while(n++<num)
    cout<<"Fibo("<<n<<")="<< Fibo(n) <<endl;
}