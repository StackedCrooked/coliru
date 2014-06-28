#include<iostream>
using namespace std;
int total=0;
int shiftingelements(int arr[],int k,int n)
{
    int i,sum=0;

    for(i=0;i<n;i++)
    {
        sum=sum+arr[i];
        if(sum>=k)
        goto output;

    }
    output:
    if(sum==k)
        {total=total+sum;
            return (i+1);}
    else if(sum>k)
    {total=total+sum-arr[i];
    return(i);}
    else
    { total=total+sum;
        return n;
    }
}
void newarray(int *arr,int n,int se)
{
    int temp1,k,i,j;
if(n!=se && se>0)
{
    for(j=0;j<se;j++)
    {
        temp1=arr[0];
    for(i=0;i<n-1;i++)
        {
            arr[i]=arr[i+1];

        }
        arr[n-1]=temp1;
    }
}
    return;
}

int main()
{
    int l,i,j,t,r,k,n,se;
    cin>>t;
    int *tot;
    tot=new int[t];
    for(l=0;l<t;l++)
    {
    cin>>r>>k>>n;
    int *arr;
    arr = new int[n];
    for(i=0;i<n;i++)
        cin>>arr[i];
    for(j=0;j<r;j++)
    {
    se=shiftingelements(arr,k,n);
    newarray(arr,n,se);
    }
    tot[l]=total;
    total=0;
    }
for(l=0;l<t;l++)
    cout<<"Case #"<<l+1<<": "<<tot[l]<<endl;
    return 0;
}
