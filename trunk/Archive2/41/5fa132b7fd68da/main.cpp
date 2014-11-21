#include <algorithm>
#include <iterator>

template<class data_iter>
bool next_combination(data_iter data_begin,  data_iter data_end, typename std::iterator_traits<data_iter>::value_type alph_begin, typename std::iterator_traits<data_iter>::value_type alph_end) 
{
    if (data_begin==data_end) return false;
    data_iter data_cur = data_begin;
    while (++*data_cur == alph_end) {
        *data_cur = alph_begin;
        ++data_cur;
        if (data_cur == data_end)
            return false;
    }
    return true;
}

#include <iostream>

int main()
{
    char data[] = {'A', 'A', 'A', '\0'};    
    do {        
        std::cout << data << '\n';
    } while(next_combination(data+0, data+3, 'A', 'C'));
    return 0;
}