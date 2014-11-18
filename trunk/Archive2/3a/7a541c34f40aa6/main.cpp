int foo( int a )
{
    int b = 0 ; 
    
    if( a < 7 ) b += 5 ;
    else if( a > 9 ) b += 6 ;
    else if( a == 7 ) b += 5 ;
    else if( a > 10 ) b += 6 ;
    else if( a == 8 ) b += 5 ;
    else if( a == 11 ) b += 6 ;
    else if( a == 9 ) b += 5 ;
    else b += 6 ;
    
    if( a < 7 ) b += 15 ;
    else if( a > 9 ) b += 26 ;
    else if( a == 7 ) b += 15 ;
    else if( a > 10 ) b += 26 ;
    else if( a == 8 ) b += 15 ;
    else if( a == 11 ) b += 26 ;
    else if( a == 9 ) b += 15 ;
    else b += 26 ;

    return b ;
    
    /*
        _Z3fooi:
        	cmpl	$9, %edi
        	movl	$20, %edx
        	movl	$32, %eax
        	cmovle	%edx, %eax
        	ret
    */
}

int bar( int a )
{
    return a > 9 ? 32 : 20 ;
    
    /*
        _Z3bari:
            cmpl	$9, %edi
        	movl	$20, %edx
        	movl	$32, %eax
        	cmovle	%edx, %eax
        	ret
    */
}