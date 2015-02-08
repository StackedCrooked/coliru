#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;
struct wektor
{
    int x;
    int y;
    wektor(){}
    wektor(int a,int b)
    {
        x = a;
        y = b;
    }
    int operator*(wektor wek)
    {
        return x*wek.y - y*wek.x;
    }
 bool operator<( wektor wek)
    {
        return (*this)*wek < 0 ? true : false;
    }
 bool operator>( wektor wek)
    {
        return (*this)*wek > 0 ? true : false;
    }
};
 bool funkcja( wektor &a, wektor &b)
{
    return a*b>0 ? true : false;
}
int main()
{
    srand(time(0));
    vector<wektor> stefan(20);
    for(int i = 0;i<20;++i)
    {
        stefan[i].x = rand()%10;
        stefan[i].y = rand()%10;
    }

    sort(stefan.begin(),stefan.end(),funkcja);
    for(int i = 0;i < 20;++i)
    {
        cout<<stefan[i].x<<" "<<stefan[i].y<<endl;
    }
}