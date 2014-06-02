
#include <cstdlib>
#include <ctime>
#include <algorithm>    // std::copy    
#include <iostream>

using namespace std;

void standardize(const int n,const float x[],float ave,float sct){
    float acc=0.0f,sum=0.0f;
    sum=std::accumulate(x,x+n,0.0f);
	ave=sum/(float)n;
	std::for_each(x,x+n,[&](const float d){acc+=(d-ave)*(d-ave);});
	sct=std::sqrt(acc/(float)(n-1));
    std::cout << "inside" << std::endl;
	std::cout << ave << std::endl;
	std::cout << sct << std::endl;
	return;
}
int main(){
    const int n=1024;
    float a2[n];
    float part0=0.0f,part1=0.0f;
    std::srand(std::time(0)); 
    for(int i=0;i<n;i++)      a2[i]=std::rand()/(float)RAND_MAX;
    standardize(n,a2,part0,part1);
    std::cout << "outside" << std::endl;
    std::cout << part0 << std::endl;
	std::cout << part1 << std::endl;
}
