typedef struct return_type { double* p ; char c[12] ; } return_type ; 

volatile return_type* main( int(*a)[23], int (*f)( int, double ) )
{
    f( *a[20], *a[5] ) ;
    
    static double d = 23.45  ;
    static return_type return_value = { &d, "hello" } ;
    return &return_value ;
}
