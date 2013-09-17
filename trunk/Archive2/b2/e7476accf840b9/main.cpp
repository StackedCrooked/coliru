# Include <iostream> 
# include <csetjmp>
 
std :: jmp_buf jump_buffer ;
 
[ [ noreturn ] ]  void ( int počítať )  
{ 
    std :: cout  <<  "("  << počet <<  ") s názvom \ n " ; 
    std :: longjmp ( jump_buffer, count + 1 ) ;   / / setjump ( ) vráti počet 1 
}
 
int main ( ) 
{ 
    int count =  setjmp ( jump_buffer ) , 
    ak  ( počet ! =  9 )  { ( počet ) ;   / / To spôsobí setjmp () ukončíte 
    } 
}