# Include <iostream> 
struct Foo { 
    int n ; 
    Foo ( )  { 
       std :: cout  <<  "static construtor \ n " ; 
    } 
    ~ Foo ( )  { 
       std :: cout  <<  "static destruidor \ n " ; 
    } 
} ; 
Foo f ;  / / static objeto 
int principal ( ) 
{ 
    std :: cout  <<  "principal função \ n " ; 
}