#include <iostream>

using namespace std;
struct zidana
{
    int n;
    int m;
};
struct zid
{
    zidana * z;
};
struct tackana
{
    int n;
    int m;
    bool p;
};
struct tacka
{
    tackana * t;
};
struct granana
{
    int n;
    int m;
    bool p;
    bool z;//ziva
    bool gr;//gore
    bool lv;
    bool ds;
    bool dl;//
};
struct grana
{
    granana * g;
};
//struct SimpleXyLink
//{
//    SimpleXyLink() : simpleXyList( new SimpleXY ) { }
//    ~SimpleXyLink() { delete simpleXyList; }
//
//    int num_xy;
//    SimpleXY *simpleXyList;
//};


int main()
{
    tackana  t[999997];
    granana  g[999996];
    zidana  z[999996];
//    tacka * t = new tacka[999997];
//    grana * g= new grana[999996];
//    zid * z= new zid[999996];
    int brug=0;
    int brpt=0;//broj ugasenih grana i prodjenih tacaka
    char c[1000][1000];
    return 0;
}
