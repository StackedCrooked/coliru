#include "iostream" // Para utilizar "cout"
#include "cassert" // Para utilizar la macro "assert()"
#include <cstdlib>

using namespace std;

class Racional {
private:
    int numerador; // Numerador
	int denominador; // Denominador. Precondición: no puede ser 0
	int calcularMCD(int num1, int num2); // Método privado para calcular el MCD de dos números mediante Euclides

public:
	/*
	Constructor que construye un numero racional a partir de su numerador y denominador 
	Parámetros:
	- Numerador: el numerador de la fracción
	- Denominador: el denominador de la fracción
	Precondición: el denominador siempre debe ser != 0
	*/
	Racional(int numerador, int denominador);

	/*
	Suma "sumando" y el objeto actual. Crea un nuevo racional con el resultado y lo devuelve 
	Parámetro: el racional que es el segundo sumando
	Retorno: un nuevo racional, fruto de sumar "sumando" con el objeto actual 
	*/
	Racional sumar(Racional sumando);

	/*
	Multiplica "multiplicador" y el objeto actual. Crea un nuevo racional con el resultado y lo devuelve 
	Parámetro: el racional que es el multiplicador
	Retorno: un nuevo racional, fruto de multiplicar "multiplicador" con el objeto actual 
	Precondición: multiplicador.denominador != 0 && denominador != 0
	*/
	Racional multiplicar(Racional multiplicador);

	/*
	Obtiene el numerador del objeto racional actual 
	Retorno: numerador de la fracción del objeto actual
	*/
	int getNumerador();

	/*
	Obtiene el denominador del objeto racional actual 
	Retorno: numerador de la fracción del objeto actual
	*/
	int getDenominador();

	/*
	Simplifica al maximo la fracción que representa al numero racional actual, 
	hayando el maximo comun denominador (MCD) del numerador y denominador, y dividiendo 
	ambos entre dicho MCD
	*/
	void simplificar();

	
	/*

	*/
	ostream& operator<< (ostream &os, const Racional &obj);
};




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

int main() { 
    // Variables para guardar numerador y denominador que capturamos por teclado
	int numerador, denominador;

	// Pedimos y creamos el primer racional
	do {
		cout << "Introduzca numerador y denominador (separado por espacios) del racional a.\nEl denominador debe ser distinto de cero: ";
		cin >> numerador;
		cin >> denominador;
	} while (denominador==0);

	Racional a(numerador, denominador);
	cout << "Racional a: " << a;
	a.simplificar();
	cout << a << endl;

}

