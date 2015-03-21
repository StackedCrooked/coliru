#include <iostream> 
#include <clocale> 
#include <cstdio>
 
int principal ( ) 
{ 
    int i, j ; 
    flutuador x, y ; 
    carvão str1 [ 10 ] , str2 [ 4 ] ; 
    wchar_t warr [ 2 ] ; 
    std :: setlocale ( LC_ALL , "en_us.utf8" ) ;
 
    caractere de entrada [ ]  = u8 "25 54.32E-1 Thompson 56789 0123 56ß水" ; 
    // parse da seguinte forma: 
    //% d: um inteiro 
    //% f: um valor de ponto flutuante 
    //% 9s: uma seqüência de no máximo 9 caracteres sem espaço em branco 
    //% 2D: de dois dígitos inteiro (dígitos 5 e 6) 
    //% f: um valor de ponto flutuante (dígitos 7, 8, 9) 
    //% * d um inteiro que isn ' t armazenados em qualquer lugar 
    // '': todos os espaços consecutivo 
    //% 3 [0-9]: uma seqüência de no máximo 3 dígitos (dígitos 5 e 6) 
    //% 2lc: dois caracteres de largura, usando vários bytes a ampla conversão 
    int ret = std :: sscanf ( entrada, "% d% f% 9s% 2d% f% * d% 3 [0-9]% 2lc" ,
                      & i, & x, str1, & j, & y, str2, warr ) ;
 
    std :: cout  <<  "convertido"  << ret <<  "campos: \ n " 
              <<  "i ="  << i <<  " \ n x = "  << x <<  ' \ n ' 
              <<  "str1 = "  << str1 <<  " \ n j = "  << j <<  ' \ n ' 
              <<  "y ="  << y <<  " \ n str2 = "  << str2 <<  ' \ n ' 
              <<  std :: hex  <<  "warr [0] = U +"  << warr [ 0 ] 
              <<  "warr [1] = U +"  << warr [ 1 ]  <<  ' \ n ' ; 
}