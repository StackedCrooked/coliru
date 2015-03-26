#include <iostream> 
#include <vector>
 
int principal ( ) 
{ 
    tente  { 
        std :: cout  <<  "lançar uma exceção inteiro ... \ n " ; 
        jogue  42 ; 
    }  captura (  int i )  { 
        std :: cout  <<  "exceção inteiro foi pego, com valor : "  << i <<  ' \ n ' ; 
    }
 
    tente  { 
        std :: cout  <<  "Criando um vetor de tamanho 5 ... \ n " ; 
        std :: vector < int > v ( 5 ) ; 
        std :: cout  <<  "Acessando o elemento 11 do vector .. . \ n " ; 
        std :: cout  << v. em ( 10 ) ;   // vector :: a () lança std :: out_of_range 
    }  captura (  const  std :: exceção & e )  {  // pego de referência para a base 
        std :: cout  <<  "uma exceção padrão foi pego, com a mensagem" " 
                  << e. o que ( )  <<  "" \ n " ; 
    }
 
}