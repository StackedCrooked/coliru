#include <iostream>
#include <math.h>
#include <vector>
using std::cout;
using std::endl;

template < class T>
class Pol;

template < class T >
const Pol< T > exp(const Pol< T >& P);

template < class T >
class Pol{
protected:
    std::vector< T > Data;

public:
    inline Pol():Data(1){}

    inline const T operator[](int i)const{return Data[i];}
    inline T& operator[](int i){return Data[i];}

    Pol& exp();
};

template < class T >
const Pol< T > exp(const Pol< T >& P){
    Pol< T > Erg(P);
    Erg[0] = exp(P[0]);           // works fine
    return Erg;
}

template < class T >
Pol< T >& Pol< T >::exp(){
    using ::exp;
    Data[0] = exp(Data[0]);     // work fine, too
    return *this;
}

int main() {
    Pol<double> P1;

    P1 = exp(P1);   // this works
    P1.exp();       // this enforces the error

    cout << "P1[0]" << P1[0] << endl;
    return 0;
}
