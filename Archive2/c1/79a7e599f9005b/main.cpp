template < typename T > struct foo
{
    T bar( T a ) const { return a + 2 ; }

    template < int N, typename U > U baz( U a ) const ;
};

// definition: specify template parameters (T,N,U)
template < typename T >
    template < int N, typename U >
        U foo<T>::baz( U a ) const { return a % N  ; }
        
// explicit instantiation: specify template arguments (int,20,short)       
template short foo<int>::baz<20,short>( short ) const ;        

int main() {}
