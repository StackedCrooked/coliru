#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

using namespace std;

int main()
{
    srand(10) ;
    for (int i=0;i<5000;i++){
    double r = (rand() % (130000-120000)) / 10000.0;//(double)rand() % (1000.0/1000.0);
    double e = -log(1-r);
    cout<<i<<". "<<r<<fixed<<setprecision(5)<<"  e."<<e<<endl;}
}