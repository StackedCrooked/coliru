

int foo()
{
    int a = 34 ; // optimised away
    long long b = a + 45 ; // optimised away
    
    int* pa = &a ; // this pointer too is optimised away
    long long* pb = &b ; // also this'
    
    return *pa < *pb ? sizeof(a) : sizeof(b) ; // return 4 ;
    
    /*
    code generated: 
    
    movl    $4, %eax
	ret
    
    equivalent to: 
    return 4 ;
    */
}

int bar()
{
    return 4 ;   
    /*
    code generated: 
    
    movl    $4, %eax
    ret
    
    */
}
