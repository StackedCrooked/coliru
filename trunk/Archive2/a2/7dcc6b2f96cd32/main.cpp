#include <iostream>
#include <string>
#include <list>

int main()
{
    std::list<std::string> seq { "1. ab", "2. cd", "3. ef", "4. gh", "5. ij",
                                   "6. kl", "7. mn", "8. op", "9. qr", "10. st" } ;
    std::size_t M = 3 ; // remove every third string

    M -= 1 ; // adjust for start with count == 1
    auto by = M % seq.size() ;

    while( seq.size() > 1 )
    {
       auto iter = seq.begin() ;
       std::advance( iter, by ) ;
       std::cout << "erase: " << *iter << '\n' ;
       seq.erase(iter) ;
       by += M ;
       by %= seq.size() ;
    }

    std::cout << "remaining: " << seq.front() << '\n' ;
}
