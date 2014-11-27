// queue.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<random>
#include<time.h>

using namespace std;
int h(int q);
int main(int argc, char** argv)
{
    mt19937 gen(time(NULL));
	double lamda = 0.95;
	poisson_distribution<int> distribution(lamda);
	//exponential_distribution<double> distribution(1);
    
	int steps=100;
	int n=0;
	int p=0;
	int q=0;
    //double a=0.0;
	for(;n<steps;n++){
		p = distribution(gen);
		q=q+p-h(q);
        cout<<"service time: "<<h(q)<<endl;
		cout<<"Q["<<n<<"]: "<<q<<" p: "<<p<<endl;
	}
	getchar();
}
int h(int q){
    mt19937 gen(time(NULL));
    exponential_distribution<double> distribution(9);
    int a = (int)distribution(gen);
	if(q==0) return 0;
	else return a;

}
