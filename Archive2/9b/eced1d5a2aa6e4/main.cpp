#include <iostream>
using namespace std;

class ArrayWrapper
{
public:
    // default constructor produces a moderately sized array
    ArrayWrapper ()
        : _p_vals( new int[ 64 ] )
        , _size( 64 )
    {
        cout << "Default constructor: " << this << endl;
    }

    explicit ArrayWrapper (int n)
        : _p_vals( new int[ n ] )
        , _size( n )
    {
        cout << "Constructor: " << this << endl;
    }

    // move constructor
    ArrayWrapper (ArrayWrapper&& other)
        : _p_vals( other._p_vals  )
        , _size( other._size )
    {
            cout << "Move constructor: " << this << " Move from: " << &other << endl;
            other._p_vals = NULL;
            other._size = 0;
    }
    
    ArrayWrapper& operator=( ArrayWrapper const & ) = delete;
    ArrayWrapper& operator=( ArrayWrapper && ) = delete;
    
    // copy constructor
    ArrayWrapper (const ArrayWrapper& other)
        : _p_vals( new int[ other._size  ] )
        , _size( other._size )
    {
            cout << "Copy constructor: " << this << endl;
            for ( int i = 0; i < _size; ++i )
            {
                    _p_vals[ i ] = other._p_vals[ i ];
            }
    }
    ~ArrayWrapper ()
    {
            cout << "Destructor: " << this << " and delete " << _p_vals << endl;
            delete [] _p_vals;
    }

private:
    int ii {};
    int *_p_vals;
    int _size;
};

ArrayWrapper foo() {
    ArrayWrapper a(7);
    cout << "Temp object created!" << endl;
    return a;
}


int main() {
    ArrayWrapper b(foo());
    cout << "Finish!" << endl;
}