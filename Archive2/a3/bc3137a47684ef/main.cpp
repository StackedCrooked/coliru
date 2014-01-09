#include <iostream>
#include <string>
using namespace std;

string EliminarCaracter (string dato, char delimitador);

int main(int argc, char *argv[]) {
    cout << EliminarCaracter("Voy a eliminar todas las 'A' minusculas", 'a');
	return 0;
}


string EliminarCaracter (string dato, char delimitador) {
	string retorno;	int posicion = 0, redimensionar = 0, caracterexiste = 0;
	int tamanho = dato.size();
	for(int i = 0; i < tamanho; i++) { 
		if (dato[i] == delimitador) {posicion = i+1;caracterexiste++;}
		retorno += dato[posicion];
		posicion++;
	}
	
	if (caracterexiste) {
		retorno = EliminarCaracter(retorno,delimitador);
	}
	
	if (dato[tamanho-1] == delimitador) redimensionar++;
	retorno.resize(tamanho-redimensionar);
	return retorno;
}