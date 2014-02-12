#include <iostream>
#include <valarray>
#include <boost/accumulators/numeric/functional/valarray.hpp>
#include <boost/accumulators/numeric/functional.hpp>

typedef std::valarray<int>    valarray_t;

int main(void) {
    int arr_length = 30;
    // initialize arr
    int* arr = new int[arr_length];
    for (int i=0; i<arr_length; i++)
        arr[i] = i;
    // Create a valarray of ints.
    valarray_t vi(arr, arr_length);
    std::valarray<bool> aaa = ( vi == vi );
    
    bool allTrue = boost::numeric::promote<bool>(aaa);
    std::cout << (allTrue ? "equal!" : "different!");
}