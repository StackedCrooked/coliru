#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>


using namespace std;

int main(void) {
    srand(time(NULL)); // semilla para generar números "aleatorios"
	unsigned int componentes = 0; // número de componentes para los arrays, es unsigned porque no habrá arrays con cantidad de componentes negativa
	unsigned int cantidadArraysParaMedia = 0; // número de arrays para el caso medio, es unsigned porque no habrá cantidad de arrays aleatorios negativa
	
	do {
		cout << "Numero de componentes de los arrays ()= 1): ";
		cin >> componentes;
	} while (componentes < 1);

	do {
		cout << "Cantidad de arrays aleatorios para el caso medio ()= 1): ";
		cin >> cantidadArraysParaMedia;
	} while (cantidadArraysParaMedia < 1);


	int **arraysParaCasoMedio[cantidadArraysParaMedia]; // array de punteros a enteros, cada uno de estos punteros apuntará al comienzo de un array de n enteros
	int *arrays = (int *)malloc(sizeof(int) * componentes);
	
	//Here: I mean, I have an array of N elements, each one of them is a pointer to the start of an array of ints... I want to fill each of that arrays with random ints -> rand()
    
    
    
    return 0;

}