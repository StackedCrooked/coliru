#include <cstdlib>
#ifndef DANA_H_
#define DANA_H_

struct Perm
{
    int n;
    int* perm;
};

template < typename T >

class Dana
{
private:
    T * wektor;
    int n; //dlugosc wektora
   
public:
    friend class Perm;
   
    Dana();
    Dana( int w ); //konstruktor
    ~Dana(); //destruktor
    Dana( const Dana & d );
   
    void pokaz() const; //pokazuje wektor
   
    Dana & operator =( const Dana & d ); //operator przypisania danych od innego obiektu
    Dana & operator =( const T * tab ); //opertor przypisania danych z tablicy dyn, pierwsza liczba jest wielkością tablicy
    T operator []( const int & idx ) const; //operator indeksowania
    operator T *() const; //opertor konwersji na tablicę parametrow
   
    Dana < T > operator *( const Perm & d ) const;
};

#endif

template < typename T > Dana < T > Dana < T >::operator *( const Perm & d ) const
{
    if( n != d.n )
    {
        exit( EXIT_FAILURE );
    }
   
    if( wektor == NULL || d.perm == NULL )
    {
        return * this;
    }
   
    Dana < T > nowy;
    nowy.wektor = new T[ d.n ];
    nowy.n = n;
   
    for( int i = 0; i < n; i++ )
    {
        nowy.wektor[ i ] = wektor[ d.perm[ i ] - 1 ];
    }
   
    return nowy;
   
}

int main()
{
    Dana<float> d;
    Perm p;
    d * p;
}

