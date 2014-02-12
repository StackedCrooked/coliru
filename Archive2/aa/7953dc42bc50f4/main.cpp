
int count_bits2( unsigned int n ) ;

int count_bits( unsigned int n )
{
    if( n == 0 ) return 0 ;
    else return n%2 + count_bits2( n/2 ) ;
}
