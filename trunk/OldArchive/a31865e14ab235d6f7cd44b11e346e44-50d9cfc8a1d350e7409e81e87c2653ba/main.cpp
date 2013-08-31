#include <algorithm>
#include <iterator>
#include <type_traits>
#include <iostream>
#include <ctime>

template< class RandomIt, class Compare >
void drise_sort( RandomIt first, RandomIt last, Compare comp )
{
    //DO A QUICKSORT DRISE
    //I KNOW YOU CAN DO IT
}


#include <string>

void do_test(const std::string* const first, const std::string* const last) {
    std::vector<std::string> output(first, last);
    drise_sort(output.begin(), output.end(), std::greater<std::string>());
    if (std::is_sorted(output.begin(), output.end(), std::greater<std::string>()) == false) {
        std::cerr << "FAILED!  input: {";
        std::copy(first, last, std::ostream_iterator<std::string>(std::cerr, ","));
        std::cerr << "}  output: {";
        std::copy(output.begin(), output.end(), std::ostream_iterator<std::string>(std::cerr, ","));
        std::cerr << "}\n";
    }
}

int main() {
    const int maxlen = 15;
    std::string strings[maxlen];
    for(int i=0; i<maxlen; ++i)
        strings[i]="0";
    clock_t begin= clock();
    clock_t stopat = begin + CLOCKS_PER_SEC; //only go for one second
    int len=1;
    for(; len<maxlen && clock()<stopat; ++len) {  
        for(unsigned increase=0; increase<((1<<(len-1))) && clock()<stopat; ++increase) {
            for(int i=1; i<len; ++i)
                strings[i][0] = strings[i-1][0] + ((increase>>(i-1))&0x1);
            do {
                do_test(strings, strings+len);
            } while(std::next_permutation(strings, strings+len) && clock()<stopat);
        }
    }
    std::cout << "completed tests up to length " << len-1;
    return 0;
}