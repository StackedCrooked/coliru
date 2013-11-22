
#include <iostream>
#include <stdio>
#include <conio>

int main (void)
{
    double costo, total, iva=0.12;


	cout<<"Ingrese el precio del artículo: ";
        
	cin>>costo;

	
	while(costo<=0||costo>1250)
	{

	cout<<"El precio ingresado esta fuera del rango. Por favor ingrese el precio del artículo nuevamente: ";
        
	cin>>costo;

	}






	iva = iva * precio;
	total = iva + precio;

	
	cout<<"El costo del producto es: " <<costo;
	cout<<endl;

	cout<<"El IVA del producto es :" <<iva;
	cout<<endl;

	cout<<"El monto total a pagar es: " <<total; 

	


				}