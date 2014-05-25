# Include <iostream> 
# include <cmath> 
# include <cerrno> 
# include <cfenv> 
# include <cstring>
 
# Pragma STDC fenv_access ON
 
int principal ( ) 
{ 
    / / uso normal 
    std :: cout  <<  "sqrt (100) ="  << sqrt ( 100 )  <<  ' \ n ' 
              <<  "sqrt (2) ="  << sqrt ( 2 )  < <  ' \ n ' 
              <<  "proporção áurea ="  <<  ( 1 + sqrt ( 5 ) ) / 2  <<  ' \ n ' ; 
    / / valores especiais 
    std :: cout  <<  "sqrt (-0) ="  < < sqrt ( - 0,0 )  <<  ' \ n ' ; 
    / / tratamento de erro 
    errno  =  0 ;  std :: feclearexcept ( FE_ALL_EXCEPT ) ; 
    std :: cout  <<  "sqrt (-1,0) ="  << sqrt ( - 1 )  <<  ' \ n ' ; 
    se ( errno  ==  EDOM ) 
        std :: cout  <<  "errno = EDOM"  <<  std :: strerror ( errno )  <<  ' \ n ' ; 
    se ( fetestexcept ( FE_INVALID ) ) 
        std: : cout  <<  "FE_INVALID levantou \ n " ; 
}