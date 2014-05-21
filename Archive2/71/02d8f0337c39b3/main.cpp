#include <iostream>
#include <math.h>

using namespace std;
int iof(int *);
void reconstr(int *,int *, int);
int iof(int *f)
{
    int n, j=0;
	cout<<"Kol-vo elementov massiva:\n";
	cin>>n;
	cout<<"Vvedite elementy massiva ("<<n<<" elementov):\n";
	for(int i=0; i<n; i++)
		cin>>*(f+i);
	cout<<'\n'<<"Massiv: ";
	for(int i=0; i<n; i++)
		cout<<*(f+i)<<' ';
	return n;
}
void reconstr(int* f1,int* f2, int n)
{
	int j=0;
	for(int i=0; i<n; i++)
		if(*(f1+i)<(-1) || *(f1+i)>1)
		{
			*(f2+j)=*(f1+i);
			j++;
		}
	for(int i=0; i<n; i++)
	{
		*(f2+j)=0;
		j++;
	}
}

void main()
{
	int n, massiv1[45],massiv2[45];
	n=iof(massiv1);
	reconstr(massiv1,massiv2,n);
	cout<<'\n'<<"Result: ";
	for(int j=0; j<n; j++)
		cout<<massiv2[j]<<' ';
	cout<<endl;
	system("pause");
}
