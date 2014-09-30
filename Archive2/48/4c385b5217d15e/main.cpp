#include <iostream>

using namespace std;

void caesar(char a[], int n)
{
    int i,j;
    int p=0;
    cout<<endl;
    for(i=0;i<n;i++)    
    {
        cout<<a[i];
        for(j=i;j<200;)         
        {   
            p = (2*n-1-2*i);
            j+=p;
            cout<<a[j];
            j+=2*n-p;
            cout<<a[j];         
        }
    }           
}

int main()
{
    int n;
    while(1)
    {
        char arr[200]={};   
        cin>>n;
        if(n==0)
            break;
        cin>>arr;
        caesar(arr,n);
    }
}