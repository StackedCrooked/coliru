// http://stackoverflow.com/questions/22883840/c-get-random-number-from-0-to-max-long-long-integer
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <limits.h>
using std::cout;
using std::endl;
    
typedef unsigned long long int UINT64;
UINT64 getRandom(const UINT64 &begin = 0, const UINT64 &end = 100) {
    //    UINT64 x = begin >= end ? 0 : begin + (UINT64) ((end - begin)*r/(double)RAND_MAX);
    return begin >= end ? 0 : begin + (UINT64) rand()*((end - begin)/RAND_MAX);
}
    
int main( int argc, char *argv[] )
{
    cout << getRandom(0, ULLONG_MAX) << endl;
    cout << getRandom(0, ULLONG_MAX) << endl;
    cout << getRandom(0, ULLONG_MAX) << endl;
    return 0;
}
