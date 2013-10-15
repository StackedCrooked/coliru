#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;

class FineSelector{
  int running_gops;
  long inf_N;
  long rep_sup;
  long rep_inf;
  long gop_counter;
  public:  
    FineSelector (double,int);
    long get_round();
};

FineSelector::FineSelector(double valor_medio_de_gops_a_distribuir, int numero_gops_a_distribuir)
{
    running_gops = numero_gops_a_distribuir;
 	inf_N=(long)floor(valor_medio_de_gops_a_distribuir);
 	rep_sup=(long)(floor(running_gops*valor_medio_de_gops_a_distribuir)-(inf_N)*running_gops);
 	rep_inf = running_gops-rep_sup;
	gop_counter = 0;
}


long FineSelector::get_round()
{
 rep_inf=running_gops-rep_sup-gop_counter;
 gop_counter++;

 if(rep_inf<=0) {
    rep_sup=rep_sup-1;
    return(inf_N+1);
  }

 if (rep_sup==0) {
     return (inf_N);
  }

 if (rep_sup>=rep_inf) {
	if ( (rep_sup%rep_inf) !=0 ) {
		rep_sup=rep_sup-1;
		return(inf_N+1);
	}
     	else {
	 	return(inf_N);
       }
  }
 // case rep_sup < rep_inf

 if ((rep_inf%rep_sup)!=0) {
      return(inf_N);
 }

 rep_sup=rep_sup-1;
 return(inf_N+1);
} 


int main(int argc, char* argv[])
{
  cout<<"\nHello World,\nWelcome to my first C ++ program on Ubuntu Linux\n\n"<<endl;
  
  FineSelector TEST(std::atof(argv[1]), std::atoi(argv[2]));
  for(int i=0;i<10;i++) 
    cout <<"round: " << TEST.get_round() <<endl;
  return(0);
}
