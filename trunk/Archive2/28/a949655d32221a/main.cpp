# include<iostream>
# include<math.h>
using namespace std ;
double pi ( double Pr , double Rn , double b  )
{    int s = 1.0 ;
    for (  ; !Rn<= 0.49  ; Rn = Rn - 0.5 )
       {    s  = 2*s ; }
    double Pi = 1+ b  ; double S = 1/s ;
	Pi = 2/S * cos ( 90 * ( 1 - S ) );
	Pr =  Pi / ( s * s ) ; 
	Pr = 100 * ( 1 - Pr ) ; 
 	return Pi ;
  }
 
int main()
{
      	int n ; double Pr =1.0 ; double Pi ;

	cout<<" entrer le nombre de racine exactes de  pi" << endl ;
    
	cin>> n ; double b = 1.0 ;
    for ( int a = n ; a!=0 ; a-- )
       {    b  = b / 10 ; }
    double Rn = n + b;
	Pi= pi(Pr,Rn,b) ;
	cout<<" ?  = " << Pi << endl ;
//	return 0 ;
}
