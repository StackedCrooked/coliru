#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    char arr[10];
	int n;
	cout<<"Enter string ";
	gets(arr);
	cout<<"\nEnter the number of elements ";
	cin >> n;
	cout << "\nYou entered [ " << arr << " ] and [ " << n << " ]\n";
}