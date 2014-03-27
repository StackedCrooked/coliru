#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main()
{
    std::srand( std::time(0) ) ; // once, right at the start

    const int NCHOICES = 5 ;
    const char* choices[NCHOICES] =
    {
        "Use the (system restore utility) to set a\n"
        "   restore point before running the application setup program.\n\n",

        "Use your internet security and perform a scan of all disk drives\n\n",

        "Reinstall windows if the app fails\n\n",

        "Pray for divine intervention\n\n",
        
        "Give up\n\n"
    };
    
    // http://en.cppreference.com/w/cpp/algorithm/random_shuffle
    std::random_shuffle( choices, choices + NCHOICES ) ;
    for( int i = 0 ; i < NCHOICES ; ++i ) std::cout << i+1 << ". " << choices[i] ;
}
