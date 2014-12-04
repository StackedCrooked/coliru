#include <iostream>
#include <string>
#include <cctype>

const int NCOLOURS = 6 ;
const std::string colours[NCOLOURS] = { "red", "blue", "yellow", "orange", "purple", "green" } ;

const int NSHAPES = 3 ;
const std::string shapes[NSHAPES] = { "circle", "triangle", "square" } ;

const int NCARDS = NCOLOURS * NSHAPES ;

std::string to_lower( std::string str ) // make everything lower case
{
    for( char& c : str ) c = std::tolower(c) ;
    return str ;
}

int colour_to_int( std::string colour ) // return 1-6 if valid colour, 0 if not found
{
    colour = to_lower(colour) ;
    for( int i = 0; i < NCOLOURS ; ++i ) if( colours[i] == colour ) return i+1 ;
    return 0 ; // not found
}

std::string int_to_colour( int colour_number ) // colour_number 1-6
{
    if( colour_number > 0 && colour_number <= NCOLOURS ) return colours[colour_number-1] ;
    return "" ; // not found
}

int shape_to_int( std::string shape ) // return 1-3 if valid shape, 0 if not found
{
    shape = to_lower(shape) ;
    for( int i = 0; i < NSHAPES ; ++i ) if( shapes[i] == shape ) return i+1 ;
    return 0 ; // not found
}

std::string int_to_shape( int shape_number ) // shape_number 1-3
{
    if( shape_number > 0 && shape_number <= NSHAPES ) return shapes[shape_number-1] ;
    return "" ; // not found
}

int card_number( std::string colour, std::string shape ) // numbers 1-18, 0 if not found
{
    return colour_to_int(colour) * NSHAPES + shape_to_int(shape) - NSHAPES ;
}

std::string card_description( int card_number ) // 1-18
{
    if( card_number > 0 && card_number <= NCARDS )
    {
        const int colour_number = (card_number-1) / NSHAPES  + 1 ;
        const int shape_number = (card_number-1) %  NSHAPES + 1 ;
        return int_to_colour(colour_number) + ' ' + int_to_shape(shape_number) ;
    }
    else return "" ; // not found
}

int main()
{
    std::string colour, shape ;
    std::cout << "enter colour and shape: " ;
    std::cin >> colour >> shape ; // validate input
    std::cout << "your guess is: " << colour << ' ' << shape << '\n' ;

    int random_card = 5 ;
    std::cout << "the random card is: " << card_description(random_card) << '\n' ;

    if( card_number( colour, shape ) == random_card ) std::cout << "your guess is correct\n" ;
    else std::cout << "your guess is wrong\n" ;
}
