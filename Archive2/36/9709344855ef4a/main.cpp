# Include 
# include <iterator> 
<string> # include 
# include <regex>
 
int principal ( ) 
{ 
    std :: corda s =  "Algumas pessoas, quando confrontado com um problema, pensar" 
        " \ " Eu sei, eu vou usar expressões regulares. \ " " 
        "Agora eles têm dois problemas." ;
 
    std :: regex self_regex ( "expressões regulares" ,
             std :: regex_constants :: ECMAScript  |  std :: regex_constants :: icase ) ; 
    se  ( std :: regex_search ( s, self_regex ) )  { 
        std :: cout  <<  "O texto contém a frase "expressões regulares" \ n " ; 
    }
 
    std :: regex word_regex ( "( \ \ S +) " ) ; 
    auto words_begin =  
        std :: sregex_iterator ( s. começar ( ) , s. final ( ) , word_regex ) ; 
    auto words_end =  std :: sregex_iterator ( ) ;
 
    std :: cout  <<  "encontrado" 
        <<  std :: distância ( words_begin, words_end ) 
        <<  "palavras \ n " ;
 
    const  int N =  6 ; 
    std :: cout  <<  "Palavras maior que"  << N <<  " 
     " << match_str << ' \ n ' ; } }  
         
        
           
                
        
    
 
    std :: regex long_word_regex ( "( \ \ w {7}) " ) ; 
    std :: corda new_s =  std :: regex_replace ( s, long_word_regex, "[$ e]" ) ; 
    std :: cout  << new_s < <  ' \ n ' ; 
}