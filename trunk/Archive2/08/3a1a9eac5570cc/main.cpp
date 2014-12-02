#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()

{
int varAux1,varAux2,varAux3,varAux4;
int a;
int var1,var2,var3,var4;


ifstream archivoLectura;
archivoLectura.open("informeuso.txt");


    if (archivoLectura.fail())
    {
        ofstream archivoLectura;
        archivoLectura.open("informeuso.txt");

            archivoLectura<<"linea 1: "<<0<<"\n";
            archivoLectura<<"linea 2: "<<0<<"\n";
            archivoLectura<<"linea 3: "<<0<<"\n";
            archivoLectura<<"linea 4: "<<0<<"\n";

        archivoLectura.close();
        archivoLectura.open("informeuso.txt");

    }


    archivoLectura>>var1;
    archivoLectura>>var2;
    archivoLectura>>var3;
    archivoLectura>>var4;


    varAux1 = var1;
    varAux2 = var2;
    varAux3 = var3;
    varAux4 = var4;


archivoLectura.close();


cout<<"hola"<<endl;
cout<<"programa prueba"<<endl;
cout<<"enter value from 0 to 9"<<endl;
cout<<"a: ";
cin >> a;



if (a>0 && a <3)

{
    var1 = varAux1 + 1;
}
else if(a>2 && a <6)

{
    var2 = varAux2 + 1;

}
else if (a>5 && a<8)
{
    var3 = varAux3 +1;

}
else
{
    var4 = varAux4 + 1;
}


ofstream archivoEscritura;
archivoEscritura.open("informeuso.txt");

    archivoEscritura<<"line 1-2: "<<var1<<"\n";
    archivoEscritura<<"line 3-5: "<<var2<<"\n";
    archivoEscritura<<"line 6-7: "<<var3<<"\n";
    archivoEscritura<<"line other: "<<var4<<"\n";

archivoEscritura.close();

system("pause");
return 0;
}