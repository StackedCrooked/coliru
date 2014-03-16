#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
int anu[1000000];
int calc(int a,int b,int c,int d)
{
    long long int k;
    k=(long long int)a*d*d+b*d+c;
    return k%1000000;
}
int main()
{
    int t,n,i,a,b,c,d,k;
    scanf("%d",&t);
    while(t--)
    {   
        scanf("%d %d %d %d %d",&n,&a,&b,&c,&d);
        memset(anu,0,sizeof(int)*1000000);
        anu[d]=1;
        vector<int> anu1;
        anu1.push_back(d);
        for(i=1;i<n;i++)
        {
            k=calc(a,b,c,anu1[i-1]);
            anu1.push_back(k);
            anu[k]=anu[k]?0:1;
        }
        d=0;k=0;
        printf("address of k=%d ",&k);
        for(i=0;i<1000000;i++)
        {
            if(anu[i])
                {
                if(d%2)
                k-=i;
                else
                k+=i;
                d++;
            }
        }
        printf("%d address of final k=%d\n",abs(k),&k);
    }
    return 0;
}