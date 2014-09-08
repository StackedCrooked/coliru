namespace N
{
    template <class T>
    void test ( const T & );
}

template <class T>
class R
{
    friend void N::test ( const R<T> & );
    int m;
};

template <class T>
void N::test ( const T & rec ) { rec.m; }

int main ( )
{
    R<int> r;
    N::test ( r );
}