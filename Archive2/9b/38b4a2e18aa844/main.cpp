#include <iostream>
#include <vector>
using namespace std;
 
int main() {
    int n;
	cin>>n;
	float arr[n], s;
	for (int i=0; i<n; i++)
	{
		cin>>arr[i];
	}
	s=1000000;
	for (int i=0; i<n; i++)
	{
		for (int k=(i+6); k<n; k++)
		{
			if ((arr[i]*arr[k])<s)
			{s=arr[i]*arr[k];}
		}
	}
	cout<<s<<endl;
}