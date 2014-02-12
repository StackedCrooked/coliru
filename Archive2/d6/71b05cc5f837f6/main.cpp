
#include<iostream>
void merge(int [],int, int [],int,int[]);
int main()
{
    int a[50],b[50],c[100],m,n,i;
    std::cin>>m;
    std::cin>>n;
    std::cout<<"Enter1";
    for(i=0;i<m;i++)
    std::cin>>a[i];
    for(i=0;i<n;i++)
    std::cin>>b[i];
    merge(a,m,b,n,c);
    return(0);
}
void merge(int A[],int m,int B[],int n,int C[])
{    int a,b,c;
    for(a=0,b=n-1,c=0;a<m&&b>=0;c++)
    if(A[a]<=B[b])
    C[c]=A[a];
    else
    C[c]=B[b];
std::cout<<"1111\n";
    for(int i=0;i<m+n;i++)
std::cout<<C[i];
}