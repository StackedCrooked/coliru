#include<iostream>
#include<random>
#include<time.h>

using namespace std;

int Rand_Case(double random, double p1, double p2, double p3, double p4, double p5, double p6);
int main(int argc, char** argv) {

    
	//int nstep=0;  //The number of steps in a single chain
    int nsim = 20;
    int nstep[nsim]={0};
	int x=100;
	int y=1000;        //The starting point of the first chain  
	int case_number=0;
	double p1;
	double p2;
	double p3;
	double p4;
	double p5;
	double p6;

	mt19937 gen(time(NULL));
	uniform_real_distribution<double> dist(0,1);
	
    for(int i = 0; i< nsim; i++){
            x=100;
            y=1000;
	while(x!=0 && y!=0)
	{
		nstep[i]++;
		double random = dist(gen);
		double c=0;
		c=0.1+0.1*x+0.1*y+0.2*x*y;
		p1=0.1/c;
		p2=0.1*y/c;
		p3=0.1*x*y/c;
		p4=0.1*x*y/c;
		p5=0.1*x/c;
		p6=0;
		case_number=Rand_Case(random,p1,p2,p3,p4,p5,p6);
		//cout << "simulation steps:   " << nstep << " " << "case_number: "<<case_number<<"x: "<<x<<" y: "<<y<< endl;  
		switch(case_number){
			case 1:
				break; // return (x,y)
			case 2:
				y=y-1;
				break; 
			case 3:
				y=y+1;
				break;
			case 4:
				x=x-1;
				break;
			case 5:
				x=x+1;
				break;
			case 6:
				break; // possiblitity is 0; Do nothing.
		}

	}
    

	cout << "Final simulation steps: " << nstep[i] << " " << endl;  
	cout << " x: " << x << " y: " << y << endl;  
    }
	//getchar();
	return 0;
}

int Rand_Case(double random, double p1, double p2, double p3, double p4, double p5, double p6){
	if(random < p1) return 1;
	else if(random < p1+p2) return 2;
	else if(random < p1+p2+p3) return 3;
	else if(random < p1+p2+p3+p4)return 4;
	else if(random < p1+p2+p3+p4+p5)return 5;
	else return 6;
}