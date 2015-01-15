#include <iostream>

int main()
{
    int numero = 0;

    // Capturamos numero por referencia, renombrandola a n
    auto l = [&n = numero]()
    {
        n = 666;
    };

    // Capturamos numero por referencia, renombrandola a y
    // z como copia de el valor 100
    // y t como copia del valor de la suma entre numero y 3
    auto x = [&y = numero, z = 100, t = numero + 3]()
    {
    	std::cout << y << ' ' << z << ' ' << t;
    };

    l();
    x(); // Imprime 666 100 3

    return 0;
}
