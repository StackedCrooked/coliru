#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

enum { MAX_CHARS = 141 };
static const char key_words[][MAX_CHARS] = { "programming", "cpp", "nba", "yolo" } ;
static const int N_KEYWORDS = sizeof(key_words) / sizeof( key_words[0] ) ;

bool is_key_word( const char word[MAX_CHARS] )
{
    if( word == NULL ) return false ;

    for( int i = 0 ; i < N_KEYWORDS ; ++i ) 
        if( strcmp( word, key_words[i] ) == 0 ) return true ;

    return false ;
}

char* read_alpha( char word[MAX_CHARS] )
{
    if( word != NULL )
    {
        int n = 0 ;
        int c ;
        while( ( c = getchar() ) != EOF && n < (MAX_CHARS-1) )
            if( isalpha(c) ) word[n++] = c ;
        word[n] = 0 ;    
    }
    return word ;
}

int main()
{
    char word[MAX_CHARS] ;
    read_alpha(word) ;

    char lc_word[MAX_CHARS] ;
    memcpy( lc_word, word, MAX_CHARS ) ;
    for( int i = 0 ; i < MAX_CHARS ; ++i ) lc_word[i] = tolower( lc_word[i] ) ;

    if( is_key_word(lc_word) ) puts(word) ;
}
