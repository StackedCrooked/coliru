#include <iterator>
#include <algorithm>
#include <cassert>

// takes an ordering object, like a map or an array
// get_radix_value(data, index) should evaluate to an integer index between 0 and base_count-1 inclusive.
template<int base_count, class it, class ordering_class>
void radix_sort(it first, it last, const ordering_class& get_radix_value, int max_depth, int depth=0) {
    it begin_section[base_count+1] = {first}; //these point to the current end of each base-section
    int counts[base_count] = {};
    {
        begin_section[base_count] = last; //fake subsequent section at the end to keep later parts simple
        it end_section[base_count] = {first}; //these point to the current end of each base-section
        //count how many values in each base-section
        for(it c=first; c!=last; ++c) {
            int index = get_radix_value(*c, depth);
            assert(index>=0 && index<base_count);
            ++counts[index];
        }
        //advance the iterators to the start of the start of each base-section
        for(int i=1; i<base_count; ++i) {
            begin_section[i] = std::next(begin_section[i-1], counts[i-1]);
            end_section[i] = begin_section[i];
        }
        int current_base = 0; //current_base dictates the next section with unsorted elements
        do {
            //figure out to which section the first unsorted element belongs
            int new_base = get_radix_value(*(end_section[current_base]), depth);
            //and move it there
            if (current_base != new_base)
                std::iter_swap(end_section[current_base], end_section[new_base]);
            ++end_section[new_base];
            //if there are no more unsorted elements in this section, 
            //  advance the next section with unsorted elements
            while(current_base<base_count && end_section[current_base]==begin_section[current_base+1]) 
                ++current_base;
            //loop until all sections are sorted
        } while(current_base < base_count-1);
    }
    //now for each base-section, recurse
    if (depth < max_depth) {
        for(int i=0; i<base_count; ++i) {
            if (counts[i] >= 2)
                radix_sort<base_count>(begin_section[i], begin_section[i+1], get_radix_value, max_depth, depth+1);
        }
    }
}

struct stringradix {
    stringradix() : indexes() {
        for(int i=0; i<256; ++i)
            indexes[i] = -1;
        indexes['A'] = 0;
        indexes['a'] = 0;
        indexes['C'] = 1;
        indexes['c'] = 1;
        indexes['G'] = 2;
        indexes['g'] = 2;
        indexes['T'] = 3;
        indexes['t'] = 3;
    }
    int operator()(const std::string&s, unsigned depth) const {
        assert(depth<=s.size());
        return indexes[(unsigned char)s[depth]];
    }
    signed char indexes[256];
};

#include <vector>
#include <iostream>
#include <string>
#include <ctime>

#ifdef _DEBUG
const int stringcount = 100;
#else
const int stringcount = 5000000;
#endif

std::vector<std::string> get_DNA() {
    std::vector<std::string> r;
    srand((unsigned int)time(NULL));
    r.reserve(stringcount);
    char elements[] = "AGCT";
    for(int i=0; i<stringcount; ++i) {
        char data[99];
        data[98] = '\0';
        for(int i=0; i<14; ++i) {
            int v = rand();
            data[i*7+0] = elements[(v>>0)&0x3];
            data[i*7+1] = elements[(v>>2)&0x3];
            data[i*7+2] = elements[(v>>4)&0x3];
            data[i*7+3] = elements[(v>>6)&0x3];
            data[i*7+4] = elements[(v>>8)&0x3];
            data[i*7+5] = elements[(v>>10)&0x3];
            data[i*7+6] = elements[(v>>12)&0x3];
        }
        r.push_back(std::string(data, 98));
    }
    return r;
}

int main() {
    stringradix get_radix_value;
    std::vector<std::string> data = get_DNA();
    radix_sort<4>(data.begin(), data.end(), get_radix_value, 98);
    std::cout << data[0];
    return 0;
}