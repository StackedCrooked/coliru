#include <cstdio>
#include <vector>
using namespace std;
// 0110100110010110
// 0 - 0
// 1 - 1
// 01 - 0
// 10 - 2
// 010 - 3
// 101 - 2
// 0101 - 10
// 1010 - 2
 
int p[4][2] = { {0,1}, {0,2}, {3,2}, {10,2} };
 
vector<vector<int> > s;
int code;
bool insert(int i, int val)
{
    s[i].push_back(val);
    int t = s[i].size();
    if(i<s.size()-1)
    {
        if((t+(code>>i))&1)
            return insert(i+1,val);
        return (val==s[i+1].back());
    }
    if(t>1 && s[i][t-1]==s[i][t-2])
    {
        s.push_back(vector<int>());
        if(t%2==0)
            code |= 1<<i;
        for(int j=0;j<t-1;j+=2)
            if(insert(i+1, s[i][j] == (t&1)))
                return true;
        return insert(i+1,val);
    }
    return false;
}
void tst()
{
    int n;
    scanf("%d",&n);
    s.clear();
    code = 0;
    bool wrong = false;
    s.push_back(vector<int>());
    for(int it=0;it<n;it++)
    {
        int x;
        scanf("%d",&x);
        if(wrong)
        {
            printf("-1 ");
            continue;
        }
        
        wrong = insert(0, x);
 
        if(s.back().size()>4)
            wrong = true;
 
        if(wrong)
        {
            printf("-1 ");
        }
        else
        {
            printf("%d ",code + (p[s.back().size()-1][s.back()[0]]<<(s.size()-1)));
        }
    }
    puts("");
}
 
int main()
{
    int t;
    scanf("%d",&t);
    for(;t--;)
        tst();
}
 