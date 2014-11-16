#include <iostream>
#include <vector>

int main ()
{
    std::vector<int> even_numbers ;
    std::vector<int> odd_numbers ;

    int number = 0;
	while( std::cin >> number && number != -9 ) // no prompts or other output please!
    {
        if( number%2 == 0 ) even_numbers.push_back(number) ;
        else odd_numbers.push_back(number) ;
    }

    // all of the odd values output in the reverse of the order
    // they were input in (one value per line)
    // so we use reverse_iterators
    // auto: http://www.stroustrup.com/C++11FAQ.html#auto
    for( auto iter = odd_numbers.rbegin() ; iter != odd_numbers.rend() ; ++iter )
        std::cout << *iter << '\n' ;

    // followed by all of the even values also output in the reverse ...
    for( auto iter = even_numbers.rbegin() ; iter != even_numbers.rend() ; ++iter )
        std::cout << *iter << '\n' ;
}
