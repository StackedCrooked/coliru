#include <iostream>
 
using namespace std;
 
int main(){
    int n;
	int sum = 0;
 
	cout<< "Type N greater than 5: \n";
	cin>> n;
 
	for (int i = 5; i <= n; i++)
		sum += i*i*i;
	cout<< "The sum is: " << sum << endl;
	return 0;
}
