#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
using namespace std;

const int n_vecinos=10;

double constantesAn(double t[3][3], double d_atomo[1][3], int n_atomos){


///////////////////////////////////////
// NUMERO Y DISTANCIA ENTRE VECINOS //
/////////////////////////////////////

// Puntos de la red
int n_puntos=0;
for (int i=(-n_vecinos+1);i<n_vecinos-1;++i){for (int j=(-n_vecinos+1);j<n_vecinos-1;++j){for (int k=(-n_vecinos+1);k<n_vecinos-1;++k){++n_puntos;}}}

double puntos[n_puntos][3],puntos_2[n_puntos][3];

n_puntos=0;
for (int i=(-n_vecinos+1);i<n_vecinos-1;++i)
{
for (int j=(-n_vecinos+1);j<n_vecinos-1;++j)
{
for (int k=(-n_vecinos+1);k<n_vecinos-1;++k)
{
puntos[n_puntos][0]=i*t[0][0]+j*t[1][0]+k*t[2][0];
puntos[n_puntos][1]=i*t[0][1]+j*t[1][1]+k*t[2][1];
puntos[n_puntos][2]=i*t[0][2]+j*t[1][2]+k*t[2][2];
++n_puntos;

if (n_atomos==2)
{
puntos_2[n_puntos][0]=i*t[0][0]+j*t[1][0]+k*t[2][0]+d_atomo[0][0];
puntos_2[n_puntos][1]=i*t[0][1]+j*t[1][1]+k*t[2][1]+d_atomo[0][1];
puntos_2[n_puntos][2]=i*t[0][2]+j*t[1][2]+k*t[2][2]+d_atomo[0][2];
}


}
}
}

if (n_atomos==2){n_puntos=n_puntos*2;}

//Modulo puntos respecto origen
double modulo[n_puntos];

for (int i=0;i<n_puntos;++i)
{if (n_atomos==2){
if((i<n_puntos/2)){modulo[i]=sqrt(puntos[i][0]*puntos[i][0]+puntos[i][1]*puntos[i][1]+puntos[i][2]*puntos[i][2]);}
else{modulo[i]=sqrt(puntos_2[i][0]*puntos_2[i][0]+puntos_2[i][1]*puntos_2[i][1]+puntos_2[i][2]*puntos_2[i][2]);}
}
else{modulo[i]=sqrt(puntos[i][0]*puntos[i][0]+puntos[i][1]*puntos[i][1]+puntos[i][2]*puntos[i][2]);}

}

//Ordena las componentes del vector modulo de menor a mayor. Primera componente es igual a 0 (distancia origen a si mismo)
double temp;
for(int i=0;i<n_puntos;i++)
{
for(int j=i+1;j<n_puntos;j++)
{if (modulo[i]<modulo[j])
{modulo[i]=modulo[i];}
else
{temp=modulo[i];
modulo[i]=modulo[j];
modulo[j]=temp;}
}
}

//Calcula numero de vecinos y su distancia
int n[n_vecinos],contador=0; for(int i=0;i<n_vecinos;i++){n[i]=0;}
double d[n_vecinos];



for(int i=n_atomos;i<n_puntos-1;i++) //i=0 modulo=0
{

if(abs(modulo[i]-modulo[i+1])<1e-3){++n[contador];d[contador]=modulo[i];}
else{++n[contador];d[contador]=modulo[i];++contador;}

if(contador==n_vecinos){break;}

}

////////////////////
// CONSTANTES AN //
//////////////////


double A[21];

for (int i=0;i<=20;++i)
{A[i]=0;}


for (int i=4;i<=20;++i)
{

for (int j=0;j<n_vecinos;++j)
{
A[i]+=pow(d[0]/d[j],i)*n[j];
}
}




for (int i=4;i<=20;++i)
{
//cout<<"A"<<i<<" "<<A[i]<<endl;

printf("A%d %f\n", i, A[i]);

}


}





int main () {

// Vectores de base
double t_SC[3][3]={1,0,0,0,1,0,0,0,1};
double t_FCC[3][3]={0,0.5,0.5,0.5,0,0.5,0.5,0.5,0};
double t_BCC[3][3]={-0.5,0.5,0.5,0.5,-0.5,0.5,0.5,0.5,-0.5};
double c=sqrt(8.0/3.0);
double t_HCP[3][3]={0.5,sqrt(3.0)/2.0,0,-0.5,sqrt(3.0)/2.0,0,0,0,c};


double d_atomo_unico[1][3]={0,0,0};
double d_atomo_HCP[1][3]={0,1/sqrt(3.0),c/2.0};
double d_atomo_dia[1][3]={0.25,0.25,0.25};



int tipored;

//cout<<"Tipo de red: ";
printf("Tipo de red: ");
//cin>>tipored;

//scanf("%d", &tipored);
tipored=1;

if (tipored==1)
{//cout<<"Red seleccionada: SC"<<endl;
printf("Red seleccionada: SC\n");
constantesAn(t_SC,d_atomo_unico,1);}

if (tipored ==2)
{//cout<<"Red seleccionada: FCC"<<endl;constantesAn(t_FCC);
}

if (tipored ==3)
{//cout<<"Red seleccionada: BCC"<<endl;constantesAn(t_BCC);
}













//system("pause");
}