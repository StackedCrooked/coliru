int sum( const int arr[], unsigned int n )
{
    if( n == 0 ) return 0 ;
    
    int temp = 0 ;
    if( n > 0 )temp = sum( arr+1, n-1 ) ; 
    
    return temp + arr[0] ;
}
