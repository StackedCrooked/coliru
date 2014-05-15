#include <iostream>

using std::cout;
using std::endl;

int sumaRec(int _suma){
    if (_suma > 0)
    {
        return _suma + sumaRec(--_suma);
    }
    else
        return 0;
}

int main() {
    cout << sumaRec(10) << endl;
    return 0;
}