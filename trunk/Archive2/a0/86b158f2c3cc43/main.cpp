#include <iostream>
#include <sstream>
#include <iterator>

int main() {
    std::stringstream sstr;
    sstr << "012";
    std::istream_iterator<char> it(sstr);
#ifdef original
    std::cout << *it++ << *it++ << "\n";
#else   /*  Expand  */
    #ifdef use_constant
        /*  Evaluation order does not matter to constants.    */
        #ifdef switch_evaluation_order
            char second = '1';
            char first = '0';
        #else
            char first = '0';
            char second = '1';
        #endif
    #else /* inputting from stream; order changes the content. */
        #ifdef switch_evaluation_order
            char second = *it++; // '0'
            char first = *it++; // '1'
        #else
            char first = *it++; // '0'
            char second = *it++; // '1'
        #endif
    #endif
        operator<<( operator<<(std::cout, first),  second);
#endif
    return 0;
}