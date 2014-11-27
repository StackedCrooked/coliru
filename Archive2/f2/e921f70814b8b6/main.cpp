#include <iostream>
#include <string> // #include <cstring>  ****
#include <algorithm> // **** required for std::count()
// using namespace std; // **** avoid

int main()

{
    const std::string corporation( "Amazon is an online corporation that has a vast "
                                   "array of products and services that it sells." );
    std::cout << corporation << '\n'
              << "The sentence is " << corporation.size() << " characters long.\n" ;

    // **** alert: not case-sensitive, will not count the 'A'
    const auto num_a = std::count( corporation.begin(), corporation.end(), 'a' ) ;

    std::cout << "'a' appears " << num_a << " times, which is "
              << num_a * 100.0 / corporation.size() << " percent.\n" ;

    // return 0;  // **** implied
}
