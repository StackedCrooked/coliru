//************************************
// C++ BEGINNER PARSER CLASS TUTORIAL
//************************************
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;

enum types { DELIMITER = 1, VARIABLE, NUMBER };    //DEL = 1; VAR = 2; NUM = 3.

class analyzer
{
    private:
    char *pExpresion;		// Points to the exp<b></b>ression.
    char token[80];		// Holds current token.
    char tokenType;		// Holds token's type.

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
    analyzer();					   // analyzer constructor.
    double sniff( char *exp );			// analyzer entry point.
    ~analyzer();						// analyzer destructor.
};

//************************************
// 13 analyzer constructor.
//************************************
analyzer::analyzer()
{

    pExpresion = NULL;

}

//************************************
// 14 analyzer entry point.
//************************************
double analyzer::sniff( char *exp )
{

    double culmination;

    pExpresion = exp;

    nextToken();
    if( !*token )
    {
        serror( 2 );						// No exp<b></b>ression present.
        return 0.0;
    }
    recursive1( culmination );
    if( *token ) serror( 0 );			// Last token must be null.
    return culmination;
}

//************************************
// 4 Add or subtract two terms.
//************************************
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

//************************************
// 5 Multiply or divide two factors.
//************************************
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

//************************************
// 6 Process an exponent.
//************************************
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

//************************************
// 7 Evaluate a unary + or -.
//************************************
void analyzer::recursive4( double &culmination )
{
    register char  beer;

    beer = 0;
    // if( ( tokenType == DELIMITER ) && *token == '+' || *token == '-' ) // ****
    if( ( tokenType == DELIMITER ) && ( *token == '+' || *token == '-' ) ) // for clarity
    {
        beer = *token;
        nextToken();
    }
    recursive5( culmination );
    if( beer == '-' ) culmination = -culmination;
}

//************************************
// 8 Process a parenthesized exp<b></b>ression.
//************************************
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

//************************************
// 9 Get the value of a number or variable
//************************************
void analyzer::bomb( double &culmination )
{

    switch( tokenType )
    {
        case NUMBER:
            culmination = atof( token );
            nextToken();
            return;

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

//************************************
// 11 Display a syntax error.
//************************************
void analyzer::serror( int error )
{

    // static char *e[] = // ****
    static const char *e[] = // literal strings are arrays of const char
    {
        "Syntax Error",
        "Unbalanced Parentheses",
        "No exp<b></b>ression Present"
    };

    cout << e[error] << endl;
}

//************************************
// 10 Obtain the next token.
//************************************
void analyzer::nextToken()
{

    register char *bucket;

    tokenType = 0;
    bucket = token;
    *bucket = '\0';

    if( !*pExpresion ) return; // At end of exp<b></b>ression.

    while( isspace( *pExpresion ) ) ++pExpresion; // Skip over white space.

    if( strchr( "+-*/%^=()", *pExpresion ) )
    {
        tokenType = DELIMITER;
        // Advance to next char.
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

//************************************
// 12 Return true if c is a delimiter.
//************************************
int analyzer::isdelim( char c )
{

    //if( strchr( " +-/*%^=()x", c ) || c == 9 || c == '\r' || c == 0 )
    if( strchr( " +-/*%^=()", c ) || c == 9 || c == '\r' || c == 0 )
        return 1;
    return 0;
}

//************************************
// 15 analyzer destructor.
//************************************
analyzer::~analyzer()
{

}

//************************************
//************************************
// Main function Hahahahaahaha
//************************************
int main( /*int argc, char* argv[]*/ )
{
    char expstr[80];

    analyzer equation; // Instantiates equation as an object of type analyzer.

    //for( ;; )	// Creates an infinite loop.
    {
        /*
        cout << endl << endl << endl;
        cout << "  To stop the program" << endl << endl;
        cout << "  enter a period then press return." << endl << endl;
        cout << "  To run the program" << endl << endl;
        cout << "  enter an algebraic express; for example, (12+5)*6 " << endl << endl;
        cout << "  then press return ==>\n";
        */

        cin.getline( expstr, 79 );
        std::cout << "expression: '" << expstr << "'\n\n" ;

        if( *expstr == '.' )
        {
            // equation.~analyzer(); // *** DO NOT DO THIS
            // destructor of equation will be automagically invoked 
            // when its life-time is over (when we return from main)

            // break; // ****		// Infinite loop exited by typing a period.
            return 0 ; // break statement can be used only within a loop or switch
        }

        cout << endl << endl << "  Answer is: " << equation.sniff( expstr ) << "\n\n";

        cout << endl << endl << endl;
        cout << "  ";
        // system( "PAUSE" );

        // system( "CLS" );

    };

    cout << endl << endl << endl;
    cout << "  ";
    //system( "PAUSE" );

    return 0;
}

//************************************ 