#include <iostream>
#include <algorithm>
#include <iterator>

template<class it, class mather=std::plus<typename std::iterator_traits<it>::value_type> >
bool next_increasing(it start, it end, typename std::iterator_traits<it>::value_type limit, mather plus={}) {
    bool n = true;
    it c = std::prev(end);
    *c = plus(*c, 1);
    if (*c == limit) {
        if (c == start)
            return false;
        n = next_increasing<it>(start, c, plus(limit,-1));
        it prev = std::prev(c);
        *c = plus(*prev,1);
    }
    return n;
}

// O T T O
//x      I
//________
// S T O P 

unsigned values[5]={0,1,2,3,4};
#define I values[0]
#define O values[1]
#define P values[2]
#define S values[3]
#define T values[4]

int main()
{        
    do {
        do {
            unsigned first = O*1000 + T*100 + T*10 + O;
            unsigned second = I;
            unsigned third = S*1000 + T*100 + O*10 + P;
            if (first * second == third) {
                std::cout<<"I="<<I<<" O="<<O<<" P="<<P<<" S="<<S<<" T="<<T;
                return 0;
            }            
        } while(std::next_permutation(std::begin(values), std::end(values)));
    } while(next_increasing(std::begin(values), std::end(values), 10));
    
    return 1;
}