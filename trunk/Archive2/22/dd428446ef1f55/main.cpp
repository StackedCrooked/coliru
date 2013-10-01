#include <iostream>
#include <cmath>
#include <string>
#include <vector>


int main()
{
  double i1, j1, k1, i2, j2, k2, i3, j3, k3, i0, j0, k0, teeta, AB, p1p0, p1, p2, p3, r;
    std::cout<<"\n\tEncontrar la distancia entre un plano y otro punto";
    std::cout<<"\n\tIngrese las coordenadas vectoriales  del punto 1 en cm";
	std::cout<<"\nIngrese i1:";
	std::cin>> i1 ;
	std::cout<<"\ningrese j1:";
	std::cin>> j1;
	std::cout<<"\ningrese k1:";
	std::cin>> k1 ;
	
	std::cout<<"\n\tIngrese las cooordenadas vectoriales del punto 2 en cm\n\t";
	std::cout<<"\nIngrese i2:";
	std::cin>> i2;
	std::cout<<"\nIngrese j2:";
	std::cin>> j2;
	std::cout<<"\nIngrese k2:";
	std::cin>> k2;
	
	std::cout<< "\n\tIngrese las coordenadas vectoriales del punto3 en cm\n\t";
	std::cout<<"\nIngrese i3:";
	std::cin>> i3;
	std::cout<<"\nIngrese j3:";
	std::cin>> j3;
	std::cout<<"\ningrese k3:";
	std::cin>> k3;
	
	std::cout<<"\n\tIngrese las coordenadas vectoriales del punto0 en cm\n\t";
	std::cout<<"\nIngrese i0:";
	std::cin>> i0;
	std::cout<<"\nIngrese j0:";
	std::cin>> j0;
	std::cout<<"\nIngrese k0:";
	std::cin>> k0;
	

    p1=sqrt((pow(i1,2))+(pow(j1,2))+(pow(k1,2))); 
    p2=sqrt((pow(i2,2))+(pow(j2,2))+(pow(k2,2)));
    p3=sqrt((pow(i3,2))+(pow(j3,2))+(pow(k3,2)));

   if((p1==p2)&&(p2==p3)&&(p1==p3))
    {
	std::cout<<"Datos incorrectos, no deben ser colineales";
    }
  else
    {
    AB=(((i1*j2)-(j1*i2))+((j1*k2)-(k1*j2))+((k1*i2)-(k2*i1)));
    teeta=asin(AB);
	p1p0=(((i1*j0)-(j1*i0))+((j1*k0)-(k1*j0))+((k1*i0)-(k2*i0)));
    r=cos(teeta)*p1p0;
    std::cout<<"La distancia del punto p0 del plano es ="; std::cout<< r; std::cout<<" cm ";
    }
	system("pause");

return (0);
}


