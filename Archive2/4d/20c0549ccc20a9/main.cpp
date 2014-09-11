#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <math.h>
#include <cmath>
using namespace std;

enum types { DELIMITER = 1, VARIABLE, NUMBER };    

class analyzer
{
    private:
    char *pExpresion;    	
    char token[80];		
    char tokenType;		

    void recursive1( double &culmination );
    void recursive2( double &culmination );
    void recursive3( double &culmination );
    void recursive4( double &culmination );
    void recursive5( double &culmination );
    void bomb( double &culmination );
    void nextToken();
    void serror( int error );
    int isdelim( char c );

    public:
    analyzer();					   
    double sniff( char *exp );			
    ~analyzer();						
};

analyzer::analyzer()
{

    pExpresion = NULL;

}

double analyzer::sniff( char *exp )
{

    double culmination;

    pExpresion = exp;

    nextToken();
    if( !*token )
    {
        serror( 2 );						
        return 0.0;
    }
    recursive1( culmination );
    if( *token ) serror( 0 );			
    return culmination;
}

void analyzer::recursive1( double &culmination )
{

    register char beer;
    double bucket;

    recursive2( culmination );
    while( ( beer = *token ) == '+' || beer == '-' )
    {
        nextToken();
        recursive2( bucket );
        switch( beer )
        {
            case '-':
                culmination = culmination - bucket;
                break;
            case '+':
                culmination = culmination + bucket;
                break;
        }
    }
}

void analyzer::recursive2( double &culmination )
{

    register char beer;
    double bucket;

    recursive3( culmination );
    while( ( beer = *token ) == '*' || beer == '/' || beer == '%' )
    {
        nextToken();
        recursive3( bucket );
        switch( beer )
        {
            case '*':
                culmination = culmination * bucket;
                break;
            case '/':
                culmination = culmination / bucket;
                break;
            case '%':
                culmination = ( int )culmination % ( int )bucket;
                break;
        }
    }
}

void analyzer::recursive3( double &culmination )
{

    double bucket, ex;
    register int t;

    recursive4( culmination );
    if( *token == '^' )
    {
        nextToken();
        recursive3( bucket );
        ex = culmination;
        if( bucket == 0.0 )
        {
            culmination = 1.0;
            return;
        }
        for( t = ( int )bucket - 1; t>0; --t ) culmination = culmination * ( double )ex;
    }
}

void analyzer::recursive4( double &culmination )
{
    register char  beer;

    beer = 0;

    if( ( tokenType == DELIMITER ) && ( *token == '+' || *token == '-' ) ) 
    {
        beer = *token;
        nextToken();
    }
    recursive5( culmination );
    if( beer == '-' ) culmination = -culmination;
}

void analyzer::recursive5( double &culmination )
{

    if( ( *token == '(' ) )
    {
        nextToken();
        recursive1( culmination );
        if( *token != ')' )
            serror( 1 );
        nextToken();
    }
    else bomb( culmination );
}

void analyzer::bomb( double &culmination )
{
    switch( tokenType )
    {
        case NUMBER:
		{
            culmination = atof( token );
            nextToken();
            return;
		}
		
        case VARIABLE:
        {
            std::cout << "looking up value of variable '" << token << "' => assuming result == 999\n" ;
            culmination = 999 ; // *** hard-coded *** TODO: look up symbol table, get the actual value
            nextToken();
            return ;
        }
        
        default:
            serror( 0 );
    }
}

void analyzer::serror( int error )
{

    
    static const char *e[] = 
    {
        "Syntax Error",
        "Unbalanced Parentheses",
        "No exp<b></b>ression Present"
    };

    cout << e[error] << endl;
}

void analyzer::nextToken()
{

    register char *bucket;

    tokenType = 0;
    bucket = token;
    *bucket = '\0';

    if( !*pExpresion ) return;

    while( isspace( *pExpresion ) ) ++pExpresion;

    if( strchr( "+-*/%^=()", *pExpresion ) )
    {
        tokenType = DELIMITER;
        *bucket++ = *pExpresion++;
    }
    else if( isalpha( *pExpresion ) )
    {
        while( !isdelim( *pExpresion ) ) *bucket++ = *pExpresion++;
        tokenType = VARIABLE;
    }
    else if( isdigit( *pExpresion ) )
    {
        while( !isdelim( *pExpresion ) ) *bucket++ = *pExpresion++;
        tokenType = NUMBER;
    }

    *bucket = '\0';
}

int analyzer::isdelim( char c )
{
    if( strchr( " +-/*%^=()", c ) || c == 9 || c == '\r' || c == 0 )
        return 1;
    return 0;
}

analyzer::~analyzer()
{

}

int main( )
{
    char expstr[80];
    {
        analyzer equation;
		cout << "Enter Equation: ";
        cin.getline( expstr, 79 );
        std::cout << "expression: '" << expstr << "'\n\n" ;
        
        if( *expstr == '.' )
        {
            return 0 ;
        }
        cout << endl << endl << "  Answer is: " << equation.sniff( expstr ) << "\n\n";
        cout << endl << endl << endl;
        cout << "  ";
       
        system( "CLS" );

    };

    cout << endl << endl << endl;
    cout << "  ";
    system( "PAUSE" );

    return 0;
}