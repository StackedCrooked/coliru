#include <iostream>
using namespace std;
 
int main()
{
    int x,y,n,punkty=0;
	cin>>x>>y>>n;
 
	for(int i=0;i<n;i++)
	{
		int punkt;
		cin>>punkt;
		if(x <= punkt && y >= punkt)
			punkty=0;
		else
		{
			if(x > punkt)
				punkty+=x-punkt;
			else
				if(y < punkt)
					punkty+=punkt-y;
		}
	}
	cout<<punkty;
 
}