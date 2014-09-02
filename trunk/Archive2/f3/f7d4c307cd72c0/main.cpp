#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>


int main(){
    const int n=11;
    double x[n],a3[n],a1[n];
    
    x[0]=-0.717778;
    x[1]=-0.496843;
    x[2]=-0.429063;
    x[3]=-0.3596;
    x[4]=-0.205607;
    x[5]=0.0730536;
    x[6]=0.138018;
    x[7]=0.585526;
    x[8]=2.40104;
    x[9]=3.75268;
    x[10]=4.55704;

    a3[0]=0.790832;
    a3[1]=0.569896;
    a3[2]=0.502116;
    a3[3]=0.432653;
    a3[4]=0.343625;
    a3[5]=0.512472;
    a3[6]=0.56708;
    a3[7]=1.01459;
    a3[8]=2.32799;
    a3[9]=3.67962;
    a3[10]=4.48398;

    std::cout.precision(10);
    std::copy(a3,a3+n,a1);
	for(int i=0;i<n;i++)			a1[i]+=x[i];			
    std::sort(a1,a1+n);
    std::cout << "original array" << std::endl;
    for(int i=0;i<n;i++)            std::cout << a1[i] << std::endl;
    std::cout << "---" << std::endl;
    int n_1=std::unique(a1,a1+n)-a1;
    std::cout << "length of unique subarray " << n_1 << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "unique array" << std::endl;
    for(int i=0;i<n_1;i++)         std::cout << a1[i] << std::endl;
    std::cout << "---" << std::endl;	
}