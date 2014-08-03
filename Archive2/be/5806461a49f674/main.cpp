#include <cstdio>
#include <cstdlib>
#include <cassert>

// (En realidad no hace falta porque no utilizamos std::cout.)
// #include <iostream>
// using namespace std;

#ifndef _tTrozo_
#define _tTrozo_

    typedef struct
    {
        float altura, trozoini, trozofin;

    } Trozo;

#endif // _tTrozo_

//const int TMAX = 499; // El TAD puede albergar un máximo de 500 trozos.
const int TMAX = 500; // El TAD puede albergar un máximo de 500 trozos.

#ifndef FUNCION_TROZOS_H
#define FUNCION_TROZOS_H

class FuncionTrozos
{
public:
    FuncionTrozos();  //Constructor

    void insertar(float inicio, float fin, float y);
    
    // Tipo de retorno float, no void.
    float valor_en_punto(float punto);


private:
    Trozo vTrozos[TMAX];
    int numTrozos;

    bool iguales(float a, float b);
};

#endif // FUNCION_TROZOS_H

//AYUDA, NO SE COMO HACER UN CONSTRUCTOR
/******************************************
CONSTRUCTOR
---------------
Debe construir una funcion no definida en ningun punto (sin trozos)
********************************************/
FuncionTrozos::FuncionTrozos()
{
    numTrozos = 0;
}

bool FuncionTrozos::iguales(float a, float b)
{
    return abs(a - b) < 0.00001;
}

/******************************************
INSERTAR
---------------
Cada trozo representa un intervalo [a,b).
Cada trozo debe tener tama?o >0  --> ERROR y finalizar ejecuci?n del programa.
Cada nuevo trozo sucesor directo del ultimo.... [a,b),[b,c)...
El primer trozo puede ser cualquiera.
********************************************/
void FuncionTrozos::insertar(float inicio, float fin, float y)
{
    // Los paréntesis no son necesarios.
    //  El operador '+' liga más fuerte que '=='.
    assert (numTrozos < TMAX);
    assert (inicio < fin);

    if (numTrozos > 0)
        // Importante (1)
        assert(iguales(inicio, vTrozos[numTrozos - 1].trozofin));

    ++numTrozos;

    vTrozos[numTrozos].trozoini = inicio;
    vTrozos[numTrozos].trozofin = fin;
    vTrozos[numTrozos].altura = y;

    /*
    if(numTrozos == 0) //VACIO
    {
        
        cout << "Introduce el inicio del trozo: " << end;
        cin >> inicio;

        cout << "Introduce el final del trozo: " << end;
        cin >> fin;

        assert ((inicio - fin) <=0);

        numTrozos++;

        vTrozos[numTrozos].trozoini=inicio;
        vTrozos[numTrozos].trozofin=fin;

        cout << "Introduce la altura del trozo:" << end;
        cin >> vTrozos[numTrozos].altura;

    } else { //para introducir desde el 2? hasta el ultimo
        cout << "Introduce el inicio del trozo: " << end;
        cin >> inicio;

        cout << "Introduce el final del trozo: " << end;
        cin >> fin;

        assert ((inicio - fin) <=0);
        assert (inicio !=vTrozos[numTrozos].trozofin);

        numTrozos++;

        vTrozos[numTrozos].trozoini=inicio;
        vTrozos[numTrozos].trozofin=fin;

        cout << "Introduce la altura del trozo:" << end;
        cin >> vTrozos[numTrozos].altura;
    }
    */
}

/******************************************
OBTENER VALOR DE LA FUNCION EN UN PUNTO DADO
---------------
Cada trozo representa un intervalo [a,b).
Cada trozo debe tener tama?o >0  --> ERROR y finalizar ejecuci?n del programa.
Cada nuevo trozo sucesor directo del ultimo.... [a,b),[b,c)...
El primer trozo puede ser cualquiera.
Un error en caso de que la funcion no est? definida en dicho punto.
********************************************/
float FuncionTrozos::valor_en_punto(float p)
{
    assert (p < vTrozos[0].trozoini);
    assert (p > vTrozos[numTrozos-1].trozofin);

    // Termínalo ... (y si te había olvidado escribir `int i`).
    for (int i = 0; i < numTrozos; i++)
    {
        // Esto no lo puedes hacer. Debe haber un 'or', igual que antes.
        if (vTrozos[i].trozoini <= p < vTrozos[i].trozofin) {
        }
    }

}
