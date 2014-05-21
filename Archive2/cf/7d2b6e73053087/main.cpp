#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct  Bunny Bunny;

struct Bunny{
    //specified attributes
	//char *gender;
	char gender[8] ;
	
	// char *name;
	char name[16] ;
	
	// char *color;
	char color[16] ;
	
	bool radioactive_mutant_vampire;
	int age;
	
	// ptobunny *next;
	Bunny* next ;
	bool alive;
};

const char *genders() // literal string is const
{
    static const char* gender_str[] = { "Male", "Female" } ;
    return gender_str[ rand() % 2 ] ;
}

const char *names( const char *gender )
{
    if( strcmp( gender, "Male" ) == 0 ) // compare strings with strcmp
    {
        static const char* name_str[] = { "Thumper", "Jack", "Bugs", "Julius" } ;
        static const int num_names = sizeof(name_str) / sizeof( name_str[0] ) ;
        return name_str[ rand() % num_names ] ;
    }
    
    else
    {
        static const char* name_str[] = { "Pink", "Lulu", "Fluffy", "Mini" } ;
        static const int num_names = sizeof(name_str) / sizeof( name_str[0] ) ;
        return name_str[ rand() % num_names ] ;
    }
}

const char *colors()
{
        static const char* clr_str[] = { "white", "brown", "black", "spotted" } ;
        static const int num_clrs = sizeof(clr_str) / sizeof( clr_str[0] ) ;
        return clr_str[ rand() % num_clrs ] ;
}	

bool radioActivity() { return rand()%100 < 20 ; } // 20%

Bunny* newbunny()
{
    Bunny* pb = malloc( sizeof(Bunny) ) ; // allocate memory
    
    // initialise bunny
    strcpy( pb->gender, genders() ) ;
    strcpy( pb->name, names(pb->gender) ) ;
    strcpy( pb->color, colors() ) ;
    pb->radioactive_mutant_vampire = radioActivity() ;
    pb->age = 0 ;
    pb->next = NULL ;
    pb->alive = true ;
    
    return pb ;
}

int main()
{
	srand((unsigned)time(NULL));
	
    // create 11 bunnies
	Bunny* first = newbunny() ;
    int i = 0 ;
	for( Bunny* p = first ; i<10 ; ++i ) 
    { 
        p->next = newbunny() ; 
        p = p->next ; 
    }  
    
    // print out info
    for( Bunny* p = first ; p != NULL; p = p->next ) 
    {
        const char* mutant = p->radioactive_mutant_vampire ? "Radioactive" : "" ;
        printf( "%s %s %s %s\n",  p->name, p->color, p->gender, mutant ) ;
    }
    
    // free the memoty
    Bunny* p = first ;
    while( p != NULL )
    {
        Bunny* next = p->next ;
        free(p) ;
        p = next ;
    }

	return 0 ;
}
