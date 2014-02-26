#include<iostream> //(para abrir la libreria de input y output) : Cooorecto!
#include<cmath> //(para abrir la libreria de calculos matemáticos): Cooorecto!

using namespace std; // esto es para no tener que poner std::cout << "ejercicio 1a" << std::cout;

int main ()
{
    cout<<"ejercicio 1a"<<endl;
    cout<<"============"<<endl;
    const int n=2; //(que cojones es n?), esto es solo una constante que utiliza en la linea 13, lo pasa a la función pow como exponente, hace i elevado a n y como n es 2, en este caso hace i elevado al cuadrado
    for(int i=1;i<=10;i++)
    { // (esto lo entiendo, es donde inicia el cálculo en i=1, hasta cuando hasta i menores e iguales a 10 y como continua sumando de uno en uno): Cooorrecto!
        // lo de abajo es imprimir 1/i*i. El 1/i*i es lo que pone abajo de double(1.0)/pow(double(i),n)
        // el pow es una función que hace los siguiente, por ejemplo pow(x,n) te calcula x elevado a n, lo que pasa es que x tiene que ser un double porque puede tener decimales, por ejemlo puedes poner pow(3.14159, 7) que es PI elevado a 7
        cout << "i=" << i << ": 1/(i*i)=" << double(1.0)/pow(double(i),n) << endl;// (esto que pollas es????? si es que para mi que este es otro ejercicio.....no???????
    }
    //system("pause"); esto no vale para nada, es para que en windows no se cierre la ventana, pero no me gusta porque no forma parte del estándar
    return 0;
}
