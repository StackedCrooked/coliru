#include <iostream>

using namespace std;

template<typename T>
class C
{
public:
    T* val; 
    unsigned size; 
public:

    C( int s = 0 ) {
        cout << "Constructor 1" << endl; 
        size = s; 
        val = ( size ) ? new T[size] : nullptr; 
    } 

    template<class T2>
    C( const C<T2>& c2 ) {
        cout << "Constructor 2" << endl; 
        size = c2.size; 
        val = ( size ) ? new T[size] : nullptr; 
    } 
    
    C( const C<T>& c2 )
    :C<T>( c2 )
    {} 
    
    ~C() {
        cout << "~C()" << endl; 
        delete[] val; 
        val = nullptr; 
    }
};

int main()
{
    C<int>   c1( 5 );
    C<float> c2( c1 );  
    C<int>   c3( c1 ); 

    return 0;
}
