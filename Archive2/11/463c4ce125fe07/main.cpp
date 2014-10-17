#include <iostream>

int main()
{
    for( int i = 1; i <= 6; ++i )
    {
        std::cout << "outer loop: i == " << i << '\n' ;
        for ( int j = 5; j >= 1; --j )
        {
            std::cout << "\tinner loop: j == " << j
                      << "    i+j == " << i + j << '\n' ;
        }
        std::cout << "\n";
    }
}
