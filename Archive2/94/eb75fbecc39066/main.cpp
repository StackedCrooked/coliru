//http://stackoverflow.com/questions/463105/in-place-radix-sort?rq=1

#include <iterator>
#include <algorithm>
#include <cassert>

// takes an ordering object, like a map or an array
// get_radix_value(data, index) should evaluate to an integer index between 0 and radix_count-1 inclusive.
template<int radix_count, class it, class digitizer, class comparitor=std::less<typename std::iterator_traits<it>::value_type> >
inline void radix_sort(it first, it last, const digitizer& get_digit, int max_depth, const comparitor& comp={}, int depth=0) {
    it begin_bucket[radix_count+1] = {first}; //these point to the beginning of each bucket
    begin_bucket[radix_count] = last; //fake subsequent bucket at the end to keep later code simple
    int counts[radix_count] = {};
    {
        it end_bucket[radix_count] = {first}; //these point to the current end of each bucket
        //count how many values will go into each bucket
        for(it c=first; c!=last; ++c) {
            int index = get_digit(*c, depth);
            assert(index>=0 && index<radix_count);
            ++counts[index];
        }
        //advance the iterators to the start of the start of each base-bucket
        for(int i=1; i<radix_count; ++i) {
            begin_bucket[i] = std::next(begin_bucket[i-1], counts[i-1]);
            end_bucket[i] = begin_bucket[i]; //each bucket begins empty
        }
        int current_base = 0; //current_base dictates the next bucket with unsorted elements
        do {
            //figure out to which bucket the next unsorted element belongs
            int new_base = get_digit(*(end_bucket[current_base]), depth);
            //and move it there, swapping the next unsorted in that bucket to this bucket
            if (current_base != new_base)
                std::iter_swap(end_bucket[current_base], end_bucket[new_base]);
            ++end_bucket[new_base];
            //if there are no more unsorted elements in this bucket, 
            //  advance the next bucket with unsorted elements
            while(current_base<radix_count && end_bucket[current_base]==begin_bucket[current_base+1]) 
                ++current_base;
            //loop until all buckets are sorted
        } while(current_base < radix_count-1);
    }
    //now for each bucket, recurse
    if (depth < max_depth) {
        for(int i=0; i<radix_count; ++i) {
            if (counts[i] >= 2) {
                radix_sort<radix_count>(begin_bucket[i], begin_bucket[i+1], get_digit, max_depth, comp, depth+1);
            }
        }
    }
}












#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
const int stringcount = 500000;

struct dna_digitizer {
    dna_digitizer() : indexes() {
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

void do_mpd_test(std::vector<std::string> data) {
    using namespace std::chrono;
    std::cout << "MPD\t";
    auto begin = high_resolution_clock::now();

    radix_sort<4>(data.begin(), data.end(), dna_digitizer(), 98);

    auto end = high_resolution_clock::now();
    auto dur = duration_cast<milliseconds>(end-begin);
    std::cout << "found " << data[0][0] << " in " << dur.count() << "ms: ";
    if (std::is_sorted(data.begin(), data.end()))
        std::cout << "right\n";
    else
        std::cout << "WRONG\n";
}


int main() {
    try {
        std::cout << "generating DNA\n";
        std::vector<std::string> data = get_DNA();

        do_mpd_test(data);
        do_mpd_test(data);
        do_mpd_test(data);
        do_mpd_test(data);
        do_mpd_test(data);
        
    } catch (std::exception& exc) {
        std::cout << "EXCEPTION: " << exc.what();
    }

    return 0;
}