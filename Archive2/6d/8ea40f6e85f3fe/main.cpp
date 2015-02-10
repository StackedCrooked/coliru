#include <iostream>
#include "stack.h"
#include <stdio.h>
using namespace std;

#ifndef _STACK_H
#define _STACK_H
typedef struct stack * STACKPTR;
typedef double ELEMTYPE;
STACKPTR create( int );
void destroy( STACKPTR );
void push( STACKPTR, ELEMTYPE);
ELEMTYPE pop( STACKPTR );
int isempty( STACKPTR );
#endif


int main()
{
    //cout<<"Hello World!";
    int i;
    STACKPTR s = create( 10 );
    for( i=0; i<10; i++ )
    {
    push( s, i );
    }
    while( ! isempty( s ) )
    {
    printf("%lf\t", pop( s ) );
    }
    destroy( s );
    
	return 0;
}