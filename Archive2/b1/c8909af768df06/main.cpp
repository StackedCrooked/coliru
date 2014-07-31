# Include <iostream> 
# include <nuevo>
 
int principal ( ) 
{ 
    intentar  { 
        mientras que  ( verdad )  { 
            nueva int [ 100000000ul ] ; 
        } 
    }  catch  ( const std :: bad_alloc y e )  { 
        std :: cout  <<  "Asignación falló:"  << . e lo que ( )  < <  ' \ n ' ; 
    } 
}