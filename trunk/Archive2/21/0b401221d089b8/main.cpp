int foo( int a )
{
    if( a == 0 ) return 5 ;
    else if( a == 1 ) return 22 ;
    else if( a == 2 ) return 0 ;
    else if( a == 3 ) return 7 ;
    else if( a == 4 ) return 1 ;
    else if( a == 5 ) return 100 ;
    else return 50 ;
    
    /*
        _Z3fooi:                                # @_Z3fooi
        	cmpl	$5, %edi
        	ja	.LBB0_2
        	movslq	%edi, %rax
        	movl	.Lswitch.table1(,%rax,4), %eax
        	retq
        .LBB0_2:
        	movl	$50, %eax
        	retq    
    */
}

int bar( int a )
{
    switch(a)
    {
        case 0: return 5 ;
        case 1:  return 22 ;
        case 2:  return 0 ;
        case 3:  return 7 ;
        case 4:  return 1 ;
        case 5:  return 100 ;
        default: return 50 ; 
    }
    /*
        _Z3bari:                                # @_Z3bari
        	cmpl	$5, %edi
        	ja	.LBB1_2
        	movslq	%edi, %rax
        	movl	.Lswitch.table1(,%rax,4), %eax
        	retq
        .LBB1_2:
        	movl	$50, %eax
        	retq
    */
}

/*
    .Lswitch.table1:
    	.long	5                       # 0x5
    	.long	22                      # 0x16
    	.long	0                       # 0x0
    	.long	7                       # 0x7
    	.long	1                       # 0x1
    	.long	100                     # 0x64
*/
