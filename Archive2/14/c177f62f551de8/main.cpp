#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    // a question is a pair of strings; first - word ; second - hint
    // http://www.cplusplus.com/reference/utility/pair/
    using question_t = std::pair< std::string, std::string > ;

    // create the sequence of questions (words + hints)
    // http://www.mochima.com/tutorials/vectors.html
    std::vector<question_t> questions =
    {
        { "medicine", "You need it everytime you got sick !" },
        { "quark", "Elementary particle christened by MGM" },
        { "zebra", "African equid" },
        { "equinox", "Occurs in March and in september" },
        { "muffin", "Toasted and buttered yeast-leavened bread" }
    };

    // http://en.cppreference.com/w/cpp/numeric/random/srand
    std::srand( std::time(nullptr) ) ; // one-time seed of the C lcg

    // create a random permutation of questions
    // http://en.cppreference.com/w/cpp/algorithm/random_shuffle
    std::random_shuffle( std::begin(questions), std::end(questions) ) ;

    // Ask the questions one by one:
    for( const question_t& q : questions )
    {
        std::cout << "word with " << q.first.size() << " letters\n"
                   << "hint: " << q.second << "\n\n" ;

        // ...
    }
}
