#include <vector>

template < class T >
class Pol;

template < class T >
const Pol<T> exp(const Pol<T>& P);

template < class T >
class Pol{
    std::vector<T> Data;
public:
    //...
    T& operator[](int i){ return Data[i];}
    //...

    Pol& exp();
};

template < class T >
const Pol<T> exp(const Pol<T>& P){
    T Value0(exp(P[0]));    // works fine 
    //...
    return Pol<T>{};  // changed EXP_of_P
}

template< class T >
Pol<T>& Pol<T>::exp() {
    T Value0(exp(Data[0]));    // Here appears the error
    //...
    return *this;
}