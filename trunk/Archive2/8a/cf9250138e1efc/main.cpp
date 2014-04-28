#include <algorithm>
#include <vector>
#include <iterator>
struct t
{
    t(int x):a(x){}
    int a;
};
bool operator<(const t& p,const t&b)
{
    return p.a<b.a;
}

int main()
{
    std::vector<t> a,b,c;
    a.push_back(t(10));
    a.push_back(t(20));
    a.push_back(t(30));
    b.push_back(t(1));
    b.push_back(t(50));
    std::merge(a.begin(),a.end(),b.begin(),b.end(),std::back_inserter(c));
    return 0;
}
