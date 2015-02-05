// racional.cpp file


#include "Racional.h"
#include "iostream" // Para utilizar "cout"
#include "cassert" // Para utilizar la macro "assert()"
#include <cstdlib>

using namespace std;

Racional::Racional(int numerador, int denominador) {
    assert(denominador != 0); // Denominador distinto de cero
	// Calculamos el signo de la fracción y lo ponemos en el numerador
	// Por lo tanto hacemos que el denominador siempre sea positivo
	if (denominador < 0) {
		denominador = -denominador;
		numerador = -numerador;
	}

	// Guardamos el numerador y el denominador en el objeto actual
	this->numerador = numerador;
	this->denominador = denominador;
}

Racional Racional::sumar (Racional sumando) {
	// Sumamos dos fracciones: la del objeto actual (this) y la pasada como parámetro
	// Para simplificar, las llamaremos numerador1/denominador1 y numerador2/denominador2
	int numerador1 = numerador;
	int denominador1 = denominador;
	int numerador2 = sumando.numerador;
	int denominador2 = sumando.denominador;

	int nuevoDenominador; // Nuevo denominador de la fraccion resultante
	int nuevoNumerador;   // Nuevo numerador de la fracción resultante

	// El nuevo denominador común del resultado idealmente seria el mínimo comun múltiplo, pero
	// para simplificar hacemos que sea la multiplicación de ambos denominadores
	nuevoDenominador = denominador1 * denominador2;

	// A partir del nuevo denominador común, calculamos los nuevos numeradores de los sumandos
	numerador1 = numerador1 * denominador2;
	numerador2 = numerador2 * denominador1;

	// Calculamos el numerador del resultado
	nuevoNumerador = numerador1 + numerador2;

	// Calculamos el resultado y lo devolvemos
	Racional resultado(nuevoNumerador, nuevoDenominador);
	return (resultado);
}

Racional Racional::multiplicar (Racional multiplicador) {
	// Los denominadores tienen que ser distintos de 0
	assert (multiplicador.denominador != 0 && denominador != 0);

	int nuevoNumerador = numerador * multiplicador.numerador;
	int nuevoDenominador = denominador * multiplicador.denominador;

	Racional resultado (nuevoNumerador, nuevoDenominador);
	return (resultado);
}

int Racional::getNumerador () {
	return(numerador);
}

int Racional::getDenominador() {
	return(denominador);
}

void Racional::simplificar() {
	int maximoComunDivisor = calcularMCD(numerador, denominador);
	numerador /= maximoComunDivisor;
	denominador /= maximoComunDivisor;
}

int Racional::calcularMCD(int numero1, int numero2) {
	assert(numero1 >= 0);
	assert(numero2 >= 0);
	if (numero2 == 0) {
		return numero1;
	}
	else {
		return calcularMCD(numero2, (numero1%numero2));
	}
}

ostream& operator<< (ostream &os, const Racional &obj) {
	os << obj.getNumerador() << "/" << obj.getDenominador();
	return os;
}
