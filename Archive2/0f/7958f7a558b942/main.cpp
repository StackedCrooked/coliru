#include <iostream>
#include <random>
#include <ctime>

void display( unsigned int c )
{
    static const char* const pictures[] =
    {
        "          .:'      \n"
        "      __ :'__      \n"
        "   .'`  `-'  ``.   \n"
        "  :            :   \n"
        "  :            :   \n"
        "  :           :    \n"
        "   `.__.-.__.'     \n",

        "       )          \n"
        "      C,          \n"
        "     ( ~)         \n"
        "     ( ~)         \n"
        "     (~ )         \n"
        "     \\~~/         \n"
        "      \\/          \n",

        "  __________    '.  :  .'  \n"
        " /         /\\__.__'.:.'  . \n"
        " \\_________\\/  .  .':'.  . \n"
        "                .'  :  '.  \n"
     };

     static constexpr std::size_t NPICS = sizeof(pictures) / sizeof( pictures[0] ) ;

     std::cout << pictures[ c % NPICS ] ;
}

void spinner()
{
    static std::mt19937 rng( std::time(nullptr) ) ;
    static std::uniform_int_distribution<unsigned int> distribution( 0, 2 ) ;
    static const char* const colours[] = { "RED", "GREEN", "BLUE" } ;

    std::cout << "set colour " << colours[ distribution(rng) ]  << '\n' ;
    display( distribution(rng) ) ;
    std::cout << "------------------------------\n" ;
}

int main()
{
    for( int i = 0 ; i < 10 ; ++i ) spinner() ;
}
